```bash
engine/
│
├── core/
├── math/
├── memory/
├── platform/
├── input/
├── events/
├── time/
├── ecs/               (or scene/ if you stay scene-based)
├── rendering/
├── assets/
├── scripting/
├── physics/
├── audio/
├── animation/
├── ui/
├── serialization/
├── reflection/
├── plugins/
├── modding/
├── debug/
└── utilities/
```

# Core/
Files you would see:
* Application
* Engine
* EngineConfig
* LayerStack
* Logger
* Assert
* BaseObject
* Subsystem

This is where:
* Startup / shutdown 
* main loop lives
* Systems are registered
* Order of execution is controlled


# Math/
Files you would see:
* Vector2, Vector3, Vector4
* Matrix4
* Quaternion
* Transform
* MathUtils
* Random

Keep dependency free


# Memory/
Files you would see:
* Custom allocators
* Memory pools
* Arena Allocators
* Smart pointer wrappers (if needed)
* Memory tracking (for debug builds)
prevent engine bloat


# Platform/
Files you would see:
* Window creation
* File System
* Threading
* Platform input
* Dynamic library loading (important for plugins)
* Timing backend
keeps engine portable

# Input/
Files you would see:
* Keyboard
* Mouse
* Gamepad
* Input mapping system (action-based, not key-based)

Developers bind actions, not keys

# Events/
Files you would see:
* Event bus
* Signals
* Dispatcher
* Engine-wide messaging

avoids coupling

# ESC/ (Scalable) or Scene/ (Simpler)
Files you would see:
* Entity
* Component
* System
* Registry

Massive scale
Modding friendliness
Clean data-orientated design

# Rendering/
## Low Level
* Renderer
* RenderCommand
* RenderAPI
* Shader
* Texture
* Framebuffer
* Material
* Mesh
* Pipeline

## High Level
* Camera
* SceneRenderer
* BatchRenderer
* Culling
* LODSystem

these help with the massive sprites and careless programming

# Assets/
## Community and modding
* Asset manager
* Asset database
* Resource handles
* Hot reloading
* Import pipeline
## Supports
* Textures
* Models
* Audio
* Scripts
* Prefabs

this is how we keep projects clean

# Scripting/
Lua Layer
* Lua VM wrapper
* Binding system
* API exposure layer
* Sandbox controls
* Script lifecycle manager

This is NOT where game scripts live.
This is the bridge.

# Physics/ 
* Collision detection
* Rigidbody system
* Physics world
* Raycasting


# Audio/
* Audio device abstraction
* Sound loading
* 2D/3D audio
* Mixer system

# Animation/
* Skeletal animation
* Keyframes
* State machines
* Blend trees

# UI/
* I will need to go deeper on this
* It is temporary but ImGui
* until i can bootstrap the GUI with the game engine

# Serialization
* Save / Load system
* Scene serialization
* Prefab system
* Version support

for community sharing

# Reflection/
* Lua bindings
* Editor
* Modding
* AI readability
allows:
* type introspection
* property exposure
* automated documentation

helps with AI friendly design

# Plugins/
* Dynamic loading
* Version checking
* Plugin lifecycle
* Sandboxing rules
 plugins should not be able to
* Modify renderer internals directly
* Break core engine
they go through API

# Modding/
* Mod manager
* Lua environment manager
* Safe API exposure
* Game rule overrides (controlled)

this is where community systems live, turn based systems live, and mechanics packs live

# Debug/
* Profile
* Frame timing
* Debug draw
* Console
* Logging UI
* Inspector system

keeps production clean

# Utilities/
* String tools
* File helpers
* Hashing
* GUID system
* Path utilities