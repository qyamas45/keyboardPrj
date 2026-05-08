# 3D Keyboard Visualizer

A real-time 3D keyboard rendered in C++ with OpenGL. Every key press is detected from actual keyboard input and reflected visually — the key animates downward and highlights to show it's being pressed.
<img width="796" height="626" alt="image" src="https://github.com/user-attachments/assets/4e06acb0-1b0c-4bab-ae4b-e33e2a5d1711" />

<img width="796" height="626" alt="image" src="https://github.com/user-attachments/assets/d0ab2003-5f23-4a21-8d59-d1f550da5de3" />


---

## Technologies Used

| Library | Purpose |
|--------|---------|
| **OpenGL 3.3 Core** | GPU rendering pipeline |
| **GLFW** | Window creation, keyboard & mouse input |
| **GLAD** | OpenGL function loader |
| **GLM** | Vectors, matrices, 3D math |
| **FreeType** | Font loading and text rendering on key surfaces |

---

## Features

- Full keyboard layout with 66 keys across 6 rows
- Variable-width keys (Space, Shift, Enter, Backspace, Tab, Caps Lock, etc.) matching real keyboard proportions
- Real-time key press animation — keys animate down and change color on press
- FreeType text labels rendered flat on each key's top surface
- Free-look camera controlled with mouse + WASD
- Per-key color customization via `setColor()`

---

## What I Learned

### OpenGL Fundamentals
- Setting up a rendering context using GLFW and GLAD
- **VAO / VBO / EBO** — how to upload vertex data to the GPU and draw it
- The difference between `glDrawArrays` and `glDrawElements` (index buffers)
- Enabling depth testing (`GL_DEPTH_TEST`) so 3D objects occlude each other correctly
- Managing GPU resources (allocating and freeing VAOs/VBOs in constructors/destructors)

### Shaders & GLSL
- Writing vertex and fragment shaders from scratch
- Passing data from CPU to GPU using **uniforms** (`setMat4`, `setVec3`, `setBool`)
- The **Model–View–Projection (MVP)** transform pipeline — how a 3D point goes from object space to screen space
- Switching between multiple shader programs in a single frame (one for geometry, one for text)

### 3D Math with GLM
- Building a **model matrix** by chaining translate → rotate → scale
- Computing a **view matrix** from a camera's position and orientation
- Setting up a **perspective projection matrix** with FOV, aspect ratio, and near/far planes
- Matrix multiplication order and why it matters in 3D transforms

### Camera System
- Implementing a free-look camera with **yaw and pitch** driven by mouse movement
- **Delta-time based movement** so camera speed is consistent regardless of frame rate
- Scroll wheel zoom by adjusting the projection FOV

### Text Rendering with FreeType
- Loading a `.ttf` font file and rasterizing individual glyphs into OpenGL textures
- Rendering characters as **textured quads lying flat in the XZ plane** (on key tops)
- Using **advance and bearing metrics** to correctly space and center text on a key
- Preventing **z-fighting** by offsetting text slightly above the key surface (`y = 0.303`)
- Blending transparent glyph textures with `GL_SRC_ALPHA` / `GL_ONE_MINUS_SRC_ALPHA`

### Object-Oriented Design in C++
- Encapsulating geometry, GPU state, and draw logic inside classes (`Cube`, `Key`, `keyboard`)
- Each object owns its VAO/VBO/EBO and cleans them up in its destructor (RAII)
- Using `std::vector<Key>` to manage all keys with individual state (pressed, color, position)
- **Input manager pattern** — `inputManager` decouples GLFW key callbacks from the rendering objects

### Procedural Layout & Geometry
- Computing keyboard row positions **algorithmically** from layout constants (`GAP`, `ROW_D`, `PADDING`) rather than hardcoding every position
- Handling **variable-width keys** with an `adjustedSize` offset baked into the vertex data
- Auto-sizing the keyboard base `Cube` at runtime to fit all keys with uniform padding

---

## Controls

| Input | Action |
|-------|--------|
| `W A S D` | Move camera |
| Mouse | Look around |
| Scroll wheel | Zoom in/out |
| Left Shift + move | Fast camera |
| Any key | Animates the corresponding key on screen |

---

## Project Structure

```
keyboard_prj/
├── src/
│   ├── main.cpp              # Entry point, render loop, camera
│   └── objects/
│       ├── cube.cpp          # Base 3D cube geometry
│       ├── key.cpp           # Individual key geometry + press animation
│       ├── keyboard.cpp      # Layout logic, assembles all keys
│       └── character.cpp     # FreeType text rendering on key surfaces
├── include/
│   ├── cube.h
│   ├── key.h
│   ├── keyboard.h
│   ├── character.h
│   └── inputManager.h
├── shaders/
│   ├── camera.vs / camera.fs     # Geometry shaders
│   ├── text3d.vs / text3d.fs     # 3D surface text shaders
│   └── text.vs / text.fs         # 2D HUD text shaders
└── src/resources/fonts/
    └── Monocraft.ttf
```
### Sources for this project was written from scratch, but I heavily referenced the following resources to learn OpenGL and implement features:
- learnopengl.com — the go-to free tutorial site that covers everything used in this project
- docs.gl — OpenGL function reference
- OpenGL SuperBible — book for going deeper
- learncpp.com and cppreference.com — the two most useful C++ learning resources
- A Tour of C++ by Stroustrup for a more advanced read

### Reflection/Improvements:
Overall this is a beginning project for me to learn how to use OpenGL. After creating this project, there is some pointers where I can improve upon this project for the next upcoming project to learn more about certain topics.
### 1. O(n²) layout in `setupMesh()` on key.cpp
**What's wrong:** For every key, the code loops from the row start back to that key's index to sum up the x position. That's recalculating work already done for every previous key in the row.  

### 2. No shared base class for `Cube` and `Key`
**What's wrong:** Both classes independently declare `position`, `scale`, `rotationAxis`, `rotationAngle`, and their own VAO/VBO/EBO management. Any future object type will repeat the same boilerplate.  

### 3. Window resize breaks the 3D projection
**What's wrong:** `framebuffer_size_callback` only calls `glViewport` — the projection matrix aspect ratio is hardcoded as `800.0f / 600.0f` in the render loop. Resizing the window will stretch or squash the 3D scene. 

### 4. Unused Variables upon different .h files.
**What's wrong:**  Uneeded variables upon classes that weren't being used such as VAO3D and VBO3D on key.h.
