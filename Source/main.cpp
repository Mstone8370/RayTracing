
#include "Math.h"
#include "Vector.h"
#include "Color.h"
#include "Ray.h"
#include "Hittable.h"
#include "HittableList.h"
#include "Sphere.h"
#include "Interval.h"
#include "Camera.h"

#include <iostream>

int main()
{
    FHittableList World;
    World.Add(std::make_shared<FSphere>(FVector(1.0, 0.0, 0.0), 0.5));
    World.Add(std::make_shared<FSphere>(FVector(-1.0, 0.0, -100.5), 100.0));

    FCamera Camera(16.0 / 9.0, 320);
    Camera.SetSamplesPerPixel(100);

    Camera.Render(World);
}
