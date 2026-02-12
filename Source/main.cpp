
#include "Math.h"
#include "Vector.h"
#include "Color.h"
#include "Ray.h"
#include "Hittable.h"
#include "HittableList.h"
#include "Sphere.h"
#include "Interval.h"
#include "Camera.h"
#include "Material.h"

#include <iostream>

int main()
{
    std::shared_ptr<IMaterial> GroundMaterial = std::make_shared<FLambertian>(FVector(0.8, 0.8, 0.0));
    std::shared_ptr<IMaterial> CenterMaterial = std::make_shared<FLambertian>(FVector(0.1, 0.2, 0.5));
    std::shared_ptr<IMaterial> LeftMaterial = std::make_shared<FDielectric>(1/1.33);
    std::shared_ptr<IMaterial> RightMaterial = std::make_shared<FMetal>(FVector(0.8, 0.6, 0.2), 1.0);

    FHittableList World;
    World.Add(std::make_shared<FSphere>(FVector(-1.0, 0.0, -100.5), 100.0, GroundMaterial));
    World.Add(std::make_shared<FSphere>(FVector(1.2, 0.0, 0.0), 0.5, CenterMaterial));
    World.Add(std::make_shared<FSphere>(FVector(1.0, -1.0, 0.0), 0.5, LeftMaterial));
    World.Add(std::make_shared<FSphere>(FVector(1.0, 1.0, 0.0), 0.5, RightMaterial));

    FCamera Camera(16.0 / 9.0, 640);
    Camera.SetSamplesPerPixel(50);
    Camera.SetMaxDepth(50);

    Camera.Render(World);
}
