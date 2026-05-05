# Lumina

An OpenGL renderer in C++ — raw triangles up through stencil-based outlines, depth testing, lighting, and model loading.

---

## What's in the project

### Core infrastructure

**`Window`** (`src/Window.h/.cpp`)  
Wraps GLFW window creation and lifetime. Sets up the OpenGL context, handles the macOS forward-compat hint, and captures the cursor for free-look movement.

**`Shader`** (`src/shader.h`)  
Reads vertex and fragment source from disk, compiles and links them, and gives you typed uniform setters (`setMat4`, `setVec3`, `setFloat`, etc.). Destructor calls `glDeleteProgram`.

**`Camera`** (`src/Camera.h`)  
Euler-angle fly camera. WASD moves it, mouse delta rotates it, scroll changes the FOV. Returns a view matrix from `glm::lookAt`.

**`Mesh`** (`src/Mesh.h`)  
Owns a VAO/VBO/EBO for one draw call. Full rule-of-five: copy re-uploads to fresh GPU buffers, move steals the handles and zeroes the source. Vertex layout covers position, normal, UV, tangent, bitangent, and bone weights. `Draw()` binds textures by convention (`texture_diffuse1`, `texture_specular1`, …) then calls `glDrawElements`.

**`Model`** (`src/Model.h`)  
Loads arbitrary 3D files via Assimp. Walks the node tree recursively, pulls out meshes and materials, and caches textures so the same image isn't uploaded to the GPU twice.

---

## Shaders

Each pair in `res/` covers one technique, roughly in the order the concepts stack on top of each other.

### `basic` — Vertex colors
The vertex shader passes a per-vertex `vec3` color through; the fragment shader outputs it unchanged. No transforms, no lighting.

### `texture` — Texture mapping
Adds UV coordinates and a `sampler2D` uniform. The fragment shader samples it directly. Used as the main object shader in the current scene.

### `camera` — MVP transforms
Adds the Model–View–Projection stack. Position gets multiplied by `projection * view * model`, so things sit correctly in 3D as the camera moves around.

### `basic_lighting` — Phong shading
The classic three-term model:

- **Ambient** — a small constant so nothing is pitch black.
- **Diffuse** — `max(dot(normal, lightDir), 0)` — faces toward the light are brighter.
- **Specular** — `pow(max(dot(viewDir, reflectDir), 0), 32)` — a tight highlight that shifts with the viewer.

Normals go through the *normal matrix* (`transpose(inverse(model))`) to stay perpendicular to the surface when the mesh is non-uniformly scaled.

### `color` / `light_cube` — Light source geometry
`color.fs` tints an object by `lightColor * objectColor`. `light_cube` draws the light source itself as a plain white cube, outside the lighting math.

### `material` — Struct-based properties
Ambient/diffuse/specular colors and shininess move into a GLSL `struct Material`. The light gets a struct too. Cleaner than juggling separate uniforms when you want to vary materials per object.

### `lighting_map` — Texture-based maps
Swaps the flat material colors for `sampler2D diffuse` and `sampler2D specular` textures. The diffuse comes from a color map; the specular highlight is masked by a greyscale map, so painted-on details don't pick up reflections where they shouldn't.

### `light_casters` — Spotlight with soft edges
Turns the point light into a spotlight by adding a direction and `cutOff` angle. `outerCutOff` gives it a soft penumbra: `clamp((theta - outerCutOff) / epsilon, 0, 1)`. Attenuation (`1 / (constant + linear*d + quadratic*d²)`) fades the light with distance.

### `multiple_lights` — Accumulated contributions
Three structs (`DirLight`, `PointLight`, `SpotLight`), each with its own calculation function. `main()` sums the results. The standard forward-renderer pattern for mixed light types.

### `depth_testing` — Visualising the depth buffer
The fragment shader reads `gl_FragCoord.z`, converts it back to a linear view-space distance, and outputs that as greyscale. Skip the linearisation step and the whole scene goes nearly white — the perspective projection packs almost everything into the far end of the [0, 1] range.

### `stencil_testing` — Object outlines
The fragment shader outputs a flat teal color. Used as a second pass: the cubes are drawn normally first (writing `1` into the stencil buffer), then redrawn at 1.1× scale with `GL_NOTEQUAL` — so only the pixels just outside the original silhouette get the tint. Depth testing is disabled for this pass so the outline doesn't get clipped.

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
| Depth buffer linearisation | `depth_testing.fs` |
| Stencil buffer & object outlines | `stencil_testing.fs`, `main.cpp` |
| Assimp scene graph traversal | `Model::processNode()` |

---

## Dependencies

- [GLFW](https://www.glfw.org/) — window & input
- [GLAD](https://glad.dav1d.de/) — OpenGL function loader
- [GLM](https://github.com/g-truc/glm) — math (vectors, matrices, transforms)
- [stb_image](https://github.com/nothings/stb) — texture loading
- [Assimp](https://github.com/assimp/assimp) — 3D model import
