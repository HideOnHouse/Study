# Let There Be Light - Shading

## Light
- - -
빛은 물체의 표면에 닿을 때 흡수광, 산란광 등의 물체와 다양한 상호 작용을 한다. 이렇게 산란된 빛은 다른 물체의 표면에
또 닿을 수 있다. 산란(흡수되지 않은 빛)은 물체의 색을 결정한다. 또한, 표면의 매끄러운 정도나 표면과 이루는 각도에 따라 또 다르다.

## Bidirectional Reflection Distribution Function (BRDF)
- - -
- ### 수식 참조
- ### Global Lighting Model(Radiosity, Ray Tracing)에 사용된다.

## Phong Reflection Model
- ### Light = Light_ambient + Light_Diffuse + Light_specular
- ### Ambient Light  
  Small amount of light scattered about the entire scene  
  Light_ambient = Kappa_ambient(coefficient) * iLlumination_ambient
- ### Diffuse Light
  incident ray reflected at many angles  
  lambertian reflectance: same apparent brightness regardless of the viewer's angle of view  
  Light_diffuse = Kappa_diffuse * max((light_direction * surface_normal), 0) * iLlumination_diffuse  
  각도가 90보다 크면 물체의 뒷면을 이야기하므로 패스
- ### Specular Light
  mirror-like reflection of light from a surface
  Light_specular = Kappa_specular * max((reflection_direction * viewer_direction)^alpha, 0) * iLlumination_specular
- ### Light = (Diffuse + Specular) / (GL_CONSTANT_ATTENUATION + GL_LINEAR_ATTENUATION * DISTANCE + GL_QUADRATIC_ATTENUATION * (DISTANCE ** 2)) + AMBIENT
- ### Phong-Blinn Reflection Model (수식 참조)
  Specular = Kappa * max((normal * h)**alpha, 0) * illumination
- ### Computing Per-Vertex Normal (동영상 참조)
- ### Types of Light Source
  - #### Point Light
	position, attenuation
  - #### Directional Light
	direction, attenuation
  - #### Spot Light
	direction, attenuation, exponent, cutoff
	