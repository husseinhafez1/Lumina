# Lumina
A real-time renderer built in C++ and OpenGL as a learning project.

---

## Implemented
- Window and OpenGL context via GLFW/GLAD
- Shader class — file loading, compilation, uniforms
- Texture class — automatic format detection, mipmaps
- VertexBuffer, IndexBuffer, VertexBufferLayout, VertexArray abstractions
- 3D camera — mouse look, WASD movement, scroll zoom
- MVP matrix pipeline — model, view, projection transforms
- Depth testing

## Planned
- Mesh loading (Assimp)
- Phong/Blinn-Phong lighting
- Multiple light types
- Shadow mapping
- Normal mapping
- Deferred shading + SSAO
- PBR with IBL
- HDR, bloom, tone mapping
- ImGui debug UI
- Vulkan backend

---

## Building
Built with Visual Studio 2022 on Windows.

**Dependencies** (included in repo):
- GLFW
- GLAD
- GLM
- stb_image

Open `Lumina.sln` and build in Visual Studio.
