# *Texture Mapping*

- - -
Q: How can represent the details of an object?  
A: Uses images to fill inside of polygons : Large chunks image data to paint the surface object

*need to specify per-vertex texture coordinates (0, 1)사이의 범위를 가진다*

1. Generate Texture ID
2. Bind Texture ID
3. Specify Texture Data
	- Load image from file
	- select active texture unit
	- wrapping mode, filtering methods
	- specify texture data
	- specify texture sampler in shader
4. Enable texture mapping
5. Binding texture id
6. Rendering with texture coords

```C++
glGenTextures();
glBindTexture();

glActiveTexture(GL_TEXTUREi);
glTexParameter();

glTexImage2D();
	- GL_UNSIGNED_BYTE
	- GL_UNSIGNED_SHORT_5_6_5
	- GL_UNSIGNED_SHORT_4_4_4_4
	- GL_UNSIGNED_SHORT_5_5_5_1
glUniform1i(glGetUniformLocation(...), i);

glActivaTexture(GL_TEXTUREi);
glBindTexture();
glEnableVertexAttribArray(); glEnableVertexAttribPointer();
```

```C++
// variables for texture mapping
GLuint tex_id;
GLsizei width, height;
GLbyte *img_pixels;
// load an image from system

// img_pixels must locate the client-side memory of the image
// width/height should be update
// pixel format is important
// …
// Generate a texture
glGenBuffers(1, &tex_id);

// Bind a texture w/ the following OpenGL texture functions
glBindTexture(GL_TEXTURE_2D, tex_id);

// Select active texture unit 0
glActiveTexture(GL_TEXTURE0);

// Set texture parameters (wrapping modes, sampling methods)
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
// Transfer an image data in the client side to the server side

glTexImage2D(tex_id, 0, GL_RGBA, width, height, 0,
GL_RGBA, GL_UNSIGNED_BYTE, pixels);

// Specify texture sampler in shader
glUniform1i(glGetUniformLocation(program, "my_sampler"), 0);
```

```C++
// Select active texture unit
glActiveTexture(GL_TEXTURE0);

// Bind a texture w/ the following OpenGL texture functions
glBindTexture(GL_TEXTURE_2D, tex_id);

// Rendering w/ texcoords
glBindBuffer(…)
glEnableVertexAttribArray(loc_a_texcoord)
glVertexAttribPointer(loc_a_texcoord, …)
glDrawArrays(…);
glDisableClientState(loc_a_texcoord);
```

## Texture Address Mode

- - -

- GL_REPEAT: 여러번 사용해야될때
- GL_MIRROR
- GL_CLAMP_TO_EDGE: 한번만 사용할때

```C++
// texture address mode as repeat
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

// texture address mode as clamp
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
```

## Sampling Problem (Aliasing)

- - -

- pixel color = primitive color * (occupancy rate)
- magnification: 봐줄 만함
- minification: 왜곡 심함

## Texture Filtering

- - -

- nearest sampling (default)
- linear sampling (better quality)

```C++
// setting for nearest samplings
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

// setting for linear samplings
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
```

## Mipmap

- - -

efficient handling minification problem  
building an image pyramid --> 미리 축소된 것을 만들어놓는다는 이야기  
함부로 사용하면 텍스쳐끼리 엉킨 축소본이 나와서 거지같이 보일 수 있다.

```C++
// Bind texture
glBindTexture(GL_TEXTURE_2D, tex_id);

// Setting several texture parameters
glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);

// Specify texture image data
glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture_width, texture_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, texture_data);
glGenerateMipmap(GL_TEXTURE_2D); // Generate a mipmap texture, Unavailable in OpenGL 2.1
```

## FSAA(Full-Scene Anti-Aliasing) or MSAA(Multisample Anti-Aliasing)

- - -

- grid
- random
- poission (푸아송)
- jitter
- rotated grid

## MISC

- - -

- ### Environment Mapping
- ### Normal Mapping

# *Blending*

- - - 

## Alpha Blending

- - -

- billboard
	- to represent a 3D object with a textured 2D plane
	- Texture images must have alpha channels (0 ~ 1)
- physically correct model --> 복잡한 표면 반사, 실시간으로 구현하기 어려움
- *C_final = f_src C_src OP f_dst C_dst*
- painter's algorithm
  	- 알파 블랜딩을 위해서 값을 뒤에서부터 맨 위까지 정렬해야 한다
    - z-buffer algorithm이 무의미해짐
```C++
// sfactor specifies how the red, green, blue, and alpha source blending factors are computed.
// dfactor specifies how the red, green, blue, and alpha destination blending factors are computed.

// Parameters RGBA blending factors
   GL_ZERO 0 0 0 0
   GL_ONE 1 1 1 1
   GL_SRC_COLOR Rs Gs Bs As
   GL_ONE_MINUS_SRC_COLOR 1-Rs 1-Gs 1-Bs 1-As
   GL_SRC_ALPHA As As As As
   GL_ONE_MINUS_SRC_ALPHA 1-As 1-As 1-As 1-As
   GL_DST_COLOR Rd Gd Bd Ad
   GL_ONE_MINUS_DST_COLOR 1-Rd 1-Gd 1-Bd 1-Ad
   GL_DST_ALPHA Ad Ad Ad Ad
   GL_ONE_MINUS_DST_ALPHA 1-Ad 1-Ad 1-Ad 1-Ad
   GL_CONSTANT_COLOR Rc Gc Bc Ac constant blending color
   GL_ONE_MINUS_CONSTANT_COLOR 1-Rc 1-Gc 1-Bc 1-Ac (Rc, Gc, Bc, Ac)
   GL_CONSTANT_ALPHA Ac Ac Ac Ac comes from
   GL_ONE_MINUS_CONSTANT_ALPHA 1-Ac 1-Ac 1-Ac 1-Ac glBlendColor()
   GL_SRC_ALPHA_SATURATE min(As, 1-Ad) 1
	
// specify pixel arithmetic 
void glBlendFunc(GLenum sfactor, GLenum dfactor);

// specify pixel arithmetic for RGB / A separately
void glBlendFuncSeparate(GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha);
```
```C++
// mode specifies how source and destination colors are combined.

// Parameters Equation
	// GL_FUNC_ADD SRC + DST
	// GL_FUNC_SUBTRACT SRC - DST
	// GL_FUNC_REVERSE_SUBTRACT DST - SRC

// For these equations all color components are understood
// to have values in the range [0, 1].
// The results of these equations are clamped to the range [0, 1].

// specify the blend equation for RGBA
void glBlendEquation(GLenum mode);

// specify the blend equations for RGB / A separately
void glBlendEquationSeparate(GLenum modeRGB, GLenum modeAlpha);
```

## Using Alpha Blending in Modern OpenGL
- - -
- Set Pixelformt of frame buffer as RGBA
- Draw an Object with alpha channel
  - When using texture, texel should have alpha channel
- Disable depth test in OpenGL
  - `glDepthMask(GL_FALSE)` or `glDisable(GL_DEPTH_TEST)`;
- Enable blending function in OpenGL
  - `glBlendFunc(…)` or `glBlendFuncSeparate(…)`
  -` glBlendEquation(…)` or `glBlendEquationSeparate(…)`
  - `glEnable(GL_BLEND)`;
- Draw objects with a carefully selected order
- Disable blending function in OpenGL
  - `glDisable(GL_BLEND)`;
- Enable depth test in OpenGL
  - `glDepthMask(GL_TRUE)` or `glEnable(GL_DEPTH_TEST)`;
	
## Texture Blending
- - -
```
/// Multitexture Fragment Shader
precision mediump float;
varying vec2 v_texCoord;
uniform sampler2D s_baseMap;
uniform sampler2D s_lightMap;

void main() {
	vec4 baseColor;
	vec4 lightColor;
	baseColor = texture2D(s_baseMap, v_texCoord);
	lightColor = texture2D(s_lightMap, v_texCoord);
	glFragColor = baseColor * (lightColor + 0.25);
}
```
```C++
GLuint baseMapLoac, baseMapTexId;

// Bind the base map
glActiveTexture(GL_TEXTURE0);
glBindTexture(GL_TEXTURE_2D, baseMapTexId);

// Set the base map sampler to texture unit 0
glUniform1i(baseMapLoc, 0);

// Bind the light map
glActiveTexture(GL_TEXTURE1);
glBindTexture(GL_TEXTURE_2D, lightMapTexId);

// Set the base map sampler to texture unit 1
glUniform1i(lightMapLoc, 1);
```

