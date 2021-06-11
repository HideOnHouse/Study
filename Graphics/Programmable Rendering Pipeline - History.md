## History
- - -
- OpenGL Shading Language
- Geometry Shader (create, destroy primitives) --> OpenGL 3.x
- Tessellation Shader (subdivision rules) --> OpenGL 4.x
- Compute Shader (execute algorithmically  general purpose GLSL shaders) --> OpenGL 4.x

## Feature
- - -
| Feature | OpenGL ES 1.1 2002 | OpenGL ES 2.0 2007 | OpenGL ES 3.0 2012 |
|-|-|-|-|
| Texture Compression | x | x | o |
| 3D Textures | x | x | o |
| 32bit float support | x | x | o |
| Programmable Shader Pipeline | x | o | o |
| Fixed Function Pipeline | o | x | x |

## Overview
- - -
### Vertex Processor --> Clipper and primitive assembler --> Rasterizer --> Fragment Processor
Material과 Lights가 Vertex Processor에 있었던 이유 : Pixel의 개수에 비해 휠씬 적어서
