
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
    FHittableList World;
    std::shared_ptr<IMaterial> GroundMaterial = std::make_shared<FLambertian>(FVector(0.5, 0.5, 0.5));
    World.Add(std::make_shared<FSphere>(FVector(0.0, 0.0, -1000.), 1000.0, GroundMaterial));

    for (int i = -11; i < 11; ++i)
    {
        for (int j = -11; j < 11; ++j)
        {
            const double RandomMaterial = FMath::RandomDouble();
            FVector Location(i + 0.9 * FMath::RandomDouble(), j + 0.9 * FMath::RandomDouble(),  0.2);

            if ((Location - FVector(0.0, 4.0, 0.2)).Length() > 0.9)
            {
                if (RandomMaterial < 0.8)
                {
                    // Diffuse
                    FVector Albedo = FMath::RandomVector() * FMath::RandomVector();
                    std::shared_ptr<IMaterial> SphereMaterial = std::make_shared<FLambertian>(Albedo);
                    World.Add(std::make_shared<FSphere>(Location, 0.2, SphereMaterial));
                }
                else if (RandomMaterial < 0.95)
                {
                    // Metal
                    FVector Albedo = FMath::RandomVector(0.5, 1.0);
                    double Fuzziness = FMath::RandomDouble(0.0, 0.5);
                    std::shared_ptr<IMaterial> SphereMaterial = std::make_shared<FMetal>(Albedo, Fuzziness);
                    World.Add(std::make_shared<FSphere>(Location, 0.2, SphereMaterial));
                }
                else
                {
                    // Glass
                    std::shared_ptr<IMaterial> SphereMaterial = std::make_shared<FDielectric>(1.5);
                    World.Add(std::make_shared<FSphere>(Location, 0.2, SphereMaterial));
                }
            }
        }
    }

    std::shared_ptr<IMaterial> Material1 = std::make_shared<FDielectric>(1.5);
    World.Add(std::make_shared<FSphere>(FVector(0.0, 0.0, 1.0), 1.0, Material1));

    std::shared_ptr<IMaterial> Material2 = std::make_shared<FLambertian>(FVector(0.4, 0.2, 0.1));
    World.Add(std::make_shared<FSphere>(FVector(0.0, -4.0, 1.0), 1.0, Material2));

    std::shared_ptr<IMaterial> Material3 = std::make_shared<FMetal>(FVector(0.7, 0.6, 0.5), 0.0);
    World.Add(std::make_shared<FSphere>(FVector(0.0, 4.0, 1.0), 1.0, Material3));

    FCamera Camera(16.0 / 9.0, 1200);
    Camera.SetSamplesPerPixel(500);
    Camera.SetMaxDepth(50);
    Camera.SetVerticalFov(20.0); // (Horizontal FOV: 110) == (Vertical FOV: 78) at 16:9 aspect ratio
    Camera.SetLocation(FVector(-3.0, 13.0, 2.0));
    Camera.SetLookAt(FVector(0.0, 0.0, 0.0));
    Camera.SetDefocusAngle(0.6);
    Camera.SetFocusDistance(10.0);

    Camera.Render(World);
}
