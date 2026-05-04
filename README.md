# Lumina

An OpenGL renderer in C++ — raw triangles up through full model loading and lighting.

---

## What's in the project

### Core infrastructure

**`Window`** (`src/Window.h/.cpp`)  
Wraps GLFW window creation and lifetime. Sets up the OpenGL context, handles the macOS forward-compat hint, and captures the cursor for free-look movement.

**`Shader`** (`src/shader.h`)  
Reads vertex and fragment source from disk, compiles and links them, and gives you typed uniform setters (`setMat4`, `setVec3`, `setFloat`, etc.).

**`Camera`** (`src/Camera.h`)  
Euler-angle fly camera. WASD moves it, mouse delta rotates it, scroll changes the FOV. Returns a view matrix from `glm::lookAt`.

**`Mesh`** (`src/Mesh.h`)  
Owns a VAO/VBO/EBO for one draw call. Vertex layout covers position, normal, UV, tangent, bitangent, and bone weights (the last two are stubs for skinning down the road). `Draw()` binds textures by convention (`texture_diffuse1`, `texture_specular1`, …) then calls `glDrawElements`.

**`Model`** (`src/Model.h`)  
Loads arbitrary 3D files via Assimp. Walks the node tree recursively, pulls out meshes and materials, and caches textures so the same image isn't uploaded to the GPU twice.

---

## Shaders

Each pair in `res/` covers one technique, roughly in the order the concepts stack on top of each other.

### `basic` — Vertex colors
As bare as it gets. The vertex shader passes a per-vertex `vec3` color through; the fragment shader outputs it unchanged. No transforms, no lighting.

### `texture` — Texture mapping
Adds UV coordinates and two `sampler2D` uniforms. The fragment shader blends them 80/20 with `mix()`. Still no 3D transforms — positions go straight to clip space.

### `camera` — MVP transforms
Adds the Model–View–Projection stack. Position gets multiplied by `projection * view * model`, so things sit correctly in 3D as the camera moves around.

### `basic_lighting` — Phong shading
The classic three-term model:

- **Ambient** — a small constant so nothing is pitch black.
- **Diffuse** — `max(dot(normal, lightDir), 0)` — faces toward the light are brighter.
- **Specular** — `pow(max(dot(viewDir, reflectDir), 0), 32)` — a tight highlight that shifts with the viewer.

Normals go through the *normal matrix* (`transpose(inverse(model))`) to stay perpendicular to the surface when the mesh is non-uniformly scaled.

### `color` / `light_cube` — Light source geometry
`color.fs` tints an object by `lightColor * objectColor`. `light_cube` draws the light source itself as a plain white cube, unaffected by any lighting calculation.

### `material` — Struct-based properties
Ambient/diffuse/specular colors and shininess move into a GLSL `struct Material`. The light gets a struct too. Cleaner than juggling separate uniforms when you want to vary materials per object.

### `lighting_map` — Texture-based maps
Swaps the flat material colors for `sampler2D diffuse` and `sampler2D specular` textures. The diffuse comes from a color map; the specular highlight is masked by a greyscale map, so painted-on details don't pick up reflections where they shouldn't.

### `light_casters` — Spotlight with soft edges
Turns the point light into a spotlight by adding a direction and `cutOff` angle. `outerCutOff` gives it a soft penumbra: `clamp((theta - outerCutOff) / epsilon, 0, 1)`. Attenuation (`1 / (constant + linear*d + quadratic*d²)`) fades the light with distance.

### `multiple_lights` — Accumulated contributions
Three structs (`DirLight`, `PointLight`, `SpotLight`), each with its own calculation function. `main()` sums the results. The standard forward-renderer approach for mixed light types.

### `model_loading` — Textured mesh from file
Samples `texture_diffuse1` and applies MVP. The minimal shader that pairs with the `Model` class for loading `.obj` files through Assimp.

---

## Key graphics concepts

| Concept | Where it appears |
|---|---|
| VAO / VBO / EBO | `Mesh::setupMesh()` |
| Coordinate spaces (local → world → view → clip) | `camera.vs`, `basic_lighting.vs` |
| Normal matrix | `basic_lighting.vs`, `material.vs` |
| Phong reflection model | `basic_lighting.fs`, `material.fs` |
| Texture units & `glActiveTexture` | `Mesh::Draw()`, `lighting_map.fs` |
| Mipmaps & texture filtering | `Model::TextureFromFile()` |
| Light attenuation | `light_casters.fs`, `multiple_lights.fs` |
| Spotlight cone math | `light_casters.fs` |
| Assimp scene graph traversal | `Model::processNode()` |

---

## Dependencies

- [GLFW](https://www.glfw.org/) — window & input
- [GLAD](https://glad.dav1d.de/) — OpenGL function loader
- [GLM](https://github.com/g-truc/glm) — math (vectors, matrices, transforms)
- [stb_image](https://github.com/nothings/stb) — texture loading
- [Assimp](https://github.com/assimp/assimp) — 3D model import

---

## Running

1. Put a model at `models/backpack/backpack.obj` (or change the path in `main.cpp`).
2. Build with CMake — OpenGL 3.3 core profile required.
3. On launch you'll be asked whether to flip textures vertically. Say `1` for most `.obj` files out of Blender.
4. **WASD** to fly, **mouse** to look, **scroll** to zoom. **Escape** quits.
