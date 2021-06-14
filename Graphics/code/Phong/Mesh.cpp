#include "Mesh.h"

void Mesh::init_buffer_objects() {
    // TODO : initialize position, normal, index buffer
    // use your code from the previous assignment
    std::vector<float> positions;
    std::vector<float> normals;

    for (int i = 0; i < mMesh->mNumVertices; ++i) {
        positions.push_back(mMesh->mVertices[i].x);
        positions.push_back(mMesh->mVertices[i].y);
        positions.push_back(mMesh->mVertices[i].z);
        normals.push_back(mMesh->mNormals[i].x);
        normals.push_back(mMesh->mNormals[i].y);
        normals.push_back(mMesh->mNormals[i].z);
    }

    glGenBuffers(1, &position_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, position_buffer);
    glBufferData(GL_ARRAY_BUFFER, positions.size() * sizeof(float), &positions[0], GL_STATIC_DRAW);

    glGenBuffers(1, &normal_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, normal_buffer);
    glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(float), &normals[0], GL_STATIC_DRAW);

    for (int i = 0; i < mMesh->mNumFaces; ++i) {
        Face face;
        face.num_indices = mMesh->mFaces[i].mNumIndices;
        glGenBuffers(1, &face.index_buffer);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, face.index_buffer);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, face.num_indices * sizeof(GLuint), &mMesh->mFaces[i].mIndices[0],
                     GL_STATIC_DRAW);
        faces.push_back(face);
    }
}

void Mesh::draw(int loc_a_position, int loc_a_normal) {
    // TODO : draw a mesh
    // use your code from the previous assignment
    glBindBuffer(GL_ARRAY_BUFFER, position_buffer);
    glEnableVertexAttribArray(loc_a_position);
    glVertexAttribPointer(loc_a_position, 3, GL_FLOAT, GL_FALSE, 0, (void *) nullptr);

    glBindBuffer(GL_ARRAY_BUFFER, normal_buffer);
    glEnableVertexAttribArray(loc_a_normal);
    glVertexAttribPointer(loc_a_normal, 3, GL_FLOAT, GL_FALSE, 0, (void *) nullptr);

    for (const auto &face : faces) {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, face.index_buffer);
        glDrawElements(GL_TRIANGLES, face.num_indices, GL_UNSIGNED_INT, (void *) nullptr);
    }

    glDisableVertexAttribArray(loc_a_position);
    glDisableVertexAttribArray(loc_a_normal);
}

void Mesh::print_info() {
    std::cout << "print mesh info" << std::endl;

    std::cout << "num vertices " << mMesh->mNumVertices << std::endl;
    for (int i = 0; i < mMesh->mNumVertices; ++i) {
        aiVector3D vertex = mMesh->mVertices[i];
        std::cout << "  vertex  (" << vertex.x << ", " << vertex.y << ", " << vertex.z << ")" << std::endl;

        if (mMesh->mColors[0] != NULL) {
            aiColor4D color = mMesh->mColors[0][i];
            std::cout << "  color  (" << color.r << ", " << color.g << ", " << color.b << ", " << color.a << ")"
                      << std::endl;
        }
    }
}