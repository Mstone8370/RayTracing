cmake_minimum_required(VERSION 3.10)

# 프로젝트 이름과 버전
project(RayTracing VERSION 1.0 LANGUAGES CXX)

# C++17 표준 사용
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# 실행 파일 생성
add_executable(RayTracing
    Source/main.cpp
    Source/Vector.cpp
    Source/Sphere.cpp
    Source/Interval.cpp
    Source/Camera.cpp
    Source/Math.cpp
)

# 컴파일러별 경고 설정
if (MSVC)
    target_compile_options(RayTracing PRIVATE /W4)
else()
    target_compile_options(RayTracing PRIVATE -Wall -Wextra)
endif()
