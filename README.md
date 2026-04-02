# Lumina

A real-time renderer built in C++ and OpenGL, developed as a learning project to understand the fundamentals of graphics programming and the rendering pipeline.

## implemented
- RAII wrappers for GPU objects (VAO, VBO, IBO, shaders, textures)
- Phong lighting model (ambient, diffuse, specular)
- Material system with diffuse + specular texture maps
- Uniform caching for efficient shader parameter updates
- Free-look camera with mouse + keyboard input
- Multiple light types (point, directional, spot)

## in progress
- Shadow mapping
- PBR (physically based rendering) with metallic/roughness workflow
- Model loading via Assimp

## notes
**Phong lighting** — approximates how light interacts with surfaces using three components: 
ambient (base indirect light), diffuse (direct light hitting the surface), 
and specular (highlight reflection). Not physically accurate but cheap and effective.

**Texture maps** — instead of flat colors, surfaces sample from textures. 
The diffuse map controls base color, the specular map controls which parts 
of the surface are shiny (white = shiny, black = matte).

**RAII** — every GPU resource is wrapped in a C++ object. Constructor allocates on the GPU, 
destructor frees it. No manual cleanup needed.

## built with
OpenGL 3.3 · GLFW · GLAD · glm · stb_image
