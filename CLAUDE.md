# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project Overview

This is a C++ ray tracing renderer based on the "Ray Tracing in One Weekend" series. The project uses CMake as its build system and targets C++17.

**Reference**: https://raytracing.github.io/books/RayTracingInOneWeekend.html

### Coordinate System Difference

**IMPORTANT**: This project uses Unreal Engine coordinate system, which differs from the original tutorial:

**World Coordinate System**:
- **Original Tutorial**: Right-handed coordinate system
  - X: right, Y: up, Z: out of screen (camera looks at -Z)
- **This Project**: Left-handed coordinate system (Unreal Engine)
  - X: forward, Y: right, Z: up
  - Camera looks at +X direction

**Image/Screen Coordinate System**:
- (0, 0): top-left corner
- x-axis: horizontal (increases right)
- y-axis: vertical (increases down)
- Image x → World Y-axis (right)
- Image y → World -Z-axis (down)

**Coordinate Conversion**:
- Tutorial (x_right, y_up, z_depth) → Unreal (x_forward, y_right, z_up)
- Conversion formula: Tutorial (x, y, z) → Unreal (-z, x, y)

**Implications**:
- Tutorial code cannot be copied directly - all vectors must be converted
- Cross product operations: left-handed vs right-handed (verify result directions)
- Normal vectors may point in opposite directions
- Camera view direction is +X (forward) instead of -Z
- Always verify cross product and normal vector calculations

## Build System

### CMake Configuration

The project uses CMake (minimum version 3.10) with the following structure:

- **CMakeLists.txt location**: [CMakeLists.txt](CMakeLists.txt) (project root)
- **C++ Standard**: C++17 (strictly enforced, no extensions)
- **Source directory**: Source/

### Project Structure

```
RayTracing/
├── CMakeLists.txt          # Build configuration
├── Source/
│   └── main.cpp            # Main renderer code
└── build/                  # Build output (generated)
```

### Building the Project

```bash
# 1. Create and enter build directory
mkdir build
cd build

# 2. Configure with CMake (generates build files)
cmake ..

# 3. Build the project
cmake --build .

# On Windows with Visual Studio, you can specify configuration:
cmake --build . --config Release
```

### Running the Renderer

The ray tracer outputs PPM format images to stdout. To generate an image:

```bash
# From build directory (Windows)
.\Debug\RayTracing.exe > output.ppm
# or for Release build
.\Release\RayTracing.exe > output.ppm

# From build directory (Linux/Mac)
./RayTracing > output.ppm
```

## Code Architecture

### Core Abstractions

- **vec3**: 3D vector class used for points, colors, and directions
- **ray**: Ray class representing a line in 3D space (origin + direction)
- **hittable**: Abstract interface for objects that can be intersected by rays
- **material**: Abstract interface for surface materials that determine ray scattering
- **camera**: Handles ray generation and image rendering
- **interval**: Represents a range of values (for ray t-values, etc.)

### Rendering Pipeline

1. Camera generates rays for each pixel
2. Rays are tested for intersection with scene objects (hittables)
3. Materials determine how rays scatter at intersection points
4. Colors are accumulated through recursive ray bouncing
5. Final pixel colors are written in PPM format

### Compiler Warnings

The project enforces specific warnings as errors depending on the compiler:

- **MSVC**: Level 4 warnings, virtual destructor warnings as errors
- **GCC/Clang**: Non-virtual destructors, reordering, uninitialized variables, unused variables

## Current State

The repository currently contains:
- A simple CMakeLists.txt configured to build the current project
- [Source/main.cpp](Source/main.cpp) - generates a basic gradient PPM image (256x256)

When adding new source files, update the CMakeLists.txt `add_executable` command to include them. For header files, place them in the Source/ directory and include them in main.cpp or other source files.
