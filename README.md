# Ray Tracing

A C++ ray tracer based on [Ray Tracing in One Weekend](https://raytracing.github.io/books/RayTracingInOneWeekend.html).

## Key Features

- **Coordinate System**: Uses Unreal Engine coordinates (X: forward, Y: right, Z: up) instead of the tutorial's right-handed Y-up system
- **C++17** with CMake build system
- Outputs PPM format images

## Build & Run

```bash
mkdir build && cd build
cmake ..
cmake --build . --config Release
.\Release\RayTracing.exe > output.ppm
```

Or use the provided `render.bat` script from the project root.

---

# 레이 트레이싱

[Ray Tracing in One Weekend](https://raytracing.github.io/books/RayTracingInOneWeekend.html) 튜토리얼을 기반으로 한 C++ 레이 트레이서입니다.

## 주요 특징

- **좌표계**: 튜토리얼의 오른손 Y-up 좌표계 대신 언리얼 엔진 좌표계(X: 전방, Y: 우측, Z: 상단)를 사용
- **C++17** 및 CMake 빌드 시스템
- PPM 형식 이미지 출력

## 빌드 및 실행

```bash
mkdir build && cd build
cmake ..
cmake --build . --config Release
.\Release\RayTracing.exe > output.ppm
```

또는 프로젝트 루트의 `render.bat` 스크립트를 사용할 수 있습니다.

---

*This README was generated with [Claude Code](https://claude.com/code)*
