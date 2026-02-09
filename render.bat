@echo off
echo Building Release...
cmake --build build --config Release

echo Running RayTracing...
.\build\Release\RayTracing.exe > output.ppm

echo Converting to PNG...
magick output.ppm output.png

echo Done! Check output.png
