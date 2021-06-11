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


## GLSL ES Programming at a glance
- - -
```C++
[Vertex Shader Object] + [Fragment Shader Object] ==(Compile, Attach)==>
==>  Shader Program Object ([vertex shader object codes] +==link==+ [fragment shader object codes])

glCreateShader(GL_VERTEX_SHADER | GL_FRAGMENT_SHADER)
glShaderSource()
glCompileShader()
---
glAttachShader()
---
glCreateProgram()
glLinkProgram()
glUseProgram()
```

## OpenGL ES 2.0
```C++
int init() {
GLbyte vShaderStr[] = { ... };
GLbyte fShaderStr[] = { ... };

// shader and program objects
GLuint vertexShader, fragmentShader, programObject;

// create and load vertex shader
vertexShader = glCreateShader(GL_VERTEX_SHADER);
glShaderSource(vertexShader, 1, &vShaderStr, NULL);
glCompileShader(vertexShader);

// create and load fragment shader
fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
glShaderSource(fragmentShader, 1, &vShaderStr, NULL);
glCompileShader(fragmentShader);

// create program object and attach shaders
programObject = glCreateProgram();
glAttachShader(programObject, vertexShader);
glAttachShader(programObject, fragmentShader);

// bind attributes 0 ~ 7
glBindAttribLocation(programObject, 0, …);

// link the program
glLinkProgram(programObject);
}
```
```C++
int draw() {
// set viewport
glViewport(…);

// clear color/depth buffers
glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

// use the program
glUseProgram(programObject);

// load the vertex data
glVertexAttribPointer(…);
glEnableVertexAttribArray(0);

// draw with the vertex data
glDrawArrays(…);

// flush the framebuffer with double buffering
eglSwapBuffers(…);
}
```

## I/O Storage Qualifiers in OpenGL ES Shader
- - -
- ### Uniform
  global variables whose value are the same across the entire shader, R
- ### Attributes
  passed to vertex shader from OpenGL ES on a per-vertex basis (C++), R, Vertex shader only
- ### Varyings
  Provide the interface between the vertex shader, fragment shader, fixed functionality between them, R/W on vertex, R on fragment.

## Built-In Variables
- ### Vertex
    - `vec4 gl_Position` contains the positions for the current vertex
    - `vec4 glFrontFacing` indicates whether a primitive is front or back facing
    - `float gl_PointSize` contains size of rasterized points, in pixels
- ### Fragment
    - `vec4 gl_FragCoord` contains the window-relative coordinates of the current fragment
    - `bool gl_FrontFacing`
    - `vec2 gl_PointCoord` contains the coordinates of a fragment within a point

```C++
GLuint vertexShader, fragmentShader, programObject;
GLuint positionLoc, colorLoc, mvpLoc;
int init() {
programObject = glCreateProgram();
// create and load vertex/fragment shader

vertexShader = glCreateShader(GL_VERTEX_SHADER);
fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

// …

// get uniform / vertex attribute locations
positionLoc = glGetAttribLocation(programObject, "a_position");
colorLoc = glGetAttribLocation(programObject, "a_normal");
mvpLoc = glGetUniformLocation(programObject, "u_mvpMatrix");
glLinkProgram(programObject);
}

int draw () {
// …
glUseProgram(programObject);
glVertexAttribPointer(positionLoc, 3, GL_FLOAT, …);
glVertexAttribPointer(colorLoc, 3, GL_FLOAT, …);
glEnableVertexAttribArray(positionLoc);
glEnableVertexAttribArray(colorLoc);
glUniformMatrix4fv(mvpLoc, …);
glDrawArrays(...);
```

## Specifying Data
- `glGet[Uniform | Attribute]Location();`
- `glUniform();`
  - 1f, 2f, 3f, 1v, 2v, 3v, Matrix2fv, Matrix3fv...
- `glVertexAttribPointer();`
- `gl[Enable | Disable]VertexAttribArray();`