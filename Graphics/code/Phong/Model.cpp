#include "Model.h"

#include <iostream>

glm::mat4 Model::get_model_matrix() {
    glm::mat4 mat_model = glm::mat4(1.0f);
    mat_model = mat_model * glm::translate(glm::mat4(1.0f), vec_translate);
    mat_model = mat_model * mat_rotate;
    mat_model = mat_model * glm::scale(glm::mat4(1.0f), vec_scale);
    return mat_model;
}

void Model::draw(int loc_a_position,
                 int loc_a_normal,
                 int loc_u_ambient,
                 int loc_u_diffuse,
                 int loc_u_specular,
                 int loc_u_shininess) {
    for (auto &mMesh : mMeshes) {
        // TODO : send material data to GPU
        glUniform3fv(loc_u_ambient, 1, glm::value_ptr(mMesh.mMaterial.ambient));
        glUniform3fv(loc_u_diffuse, 1, glm::value_ptr(mMesh.mMaterial.diffuse));
        glUniform3fv(loc_u_specular, 1, glm::value_ptr(mMesh.mMaterial.specular));
        glUniform1f(loc_u_shininess, mMesh.mMaterial.shininess);
        mMesh.draw(loc_a_position, loc_a_normal);
    }
}

bool Model::load_model(const std::string &filename) {
    file_name = filename;
    const aiScene *scene = aiImportFile(filename.c_str(), aiProcessPreset_TargetRealtime_MaxQuality);
    if (scene == nullptr)
        return false;

    aiColor3D tmp;
    aiString name;

    for (int i = 0; i < scene->mNumMeshes; ++i) {
        Mesh mesh;
        mesh = Mesh(scene->mMeshes[i]);
        mesh.init_buffer_objects();
        int mat_idx = scene->mMeshes[i]->mMaterialIndex;
        scene->mMaterials[mat_idx]->Get(AI_MATKEY_COLOR_AMBIENT, tmp);
        glm::vec3 ambient(tmp[0], tmp[1], tmp[2]);
        scene->mMaterials[mat_idx]->Get(AI_MATKEY_COLOR_DIFFUSE, tmp);
        glm::vec3 diffuse(tmp[0], tmp[1], tmp[2]);
        scene->mMaterials[mat_idx]->Get(AI_MATKEY_COLOR_SPECULAR, tmp);
        glm::vec3 specular(tmp[0], tmp[1], tmp[2]);
        Material mat(ambient, diffuse, specular, 5.0f);
        scene->mMaterials[mat_idx]->Get(AI_MATKEY_NAME, name);
        mat.name = name.C_Str();
        mesh.set_material(mat);
        mMeshes.push_back(mesh);
    }
    return true;
}
