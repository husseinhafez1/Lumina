# Lumina
Real-time OpenGL renderer built while studying [Real-Time Rendering 4th ed.](https://www.realtimerendering.com/) and [LearnOpenGL](https://learnopengl.com/).

---

## Implemented
- Window and OpenGL context via GLFW/GLAD
- Shader class — loads from file, compiles, links, uniform setters
- VAO, VBO, EBO setup
- Vertex colors via vertex attributes

## Planned
- Textures
- 3D camera and perspective projection
- Mesh loading
- Phong/Blinn-Phong lighting
- Shadow maps
- Normal mapping
- Deferred shading + SSAO
- PBR with IBL
- HDR, bloom, tone mapping
- ImGui debug UI
- Vulkan backend alongside OpenGL

---

## RTR Notes

### Chapter 2 — The Graphics Rendering Pipeline

The pipeline has four stages: **application → geometry processing → rasterization → pixel processing**. They run in parallel. The slowest stage is the bottleneck — everything else waits on it.

**Application stage** runs on CPU. Handles physics, collision, animation, input, culling. Feeds triangles to the next stage. Can offload work to the GPU via compute shaders.

**Geometry processing** runs on GPU. All per-vertex work:
- Vertices go through a chain of spaces: model space → world space (model transform) → view/eye space (view transform) → clip space (projection)
- The view transform places the camera at the origin looking down -Z, making clipping and projection simpler
- Two projection types: orthographic (parallel lines stay parallel, used in CAD/architecture) and perspective (parallel lines converge, objects shrink with distance — matches human perception). Both expressed as 4×4 matrices
- After projection, clipping removes geometry outside the view frustum
- Optional stages — tessellation, geometry shading, stream output — exist but aren't commonly used

**Rasterization** takes triangles and determines which pixels fall inside them, then interpolates vertex data across those pixels.

**Pixel processing** runs a program per pixel to compute final color, performs depth testing for visibility.
