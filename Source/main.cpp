
#include "Math.h"
#include "Vector.h"
#include "Color.h"
#include "Ray.h"
#include "Hittable.h"
#include "HittableList.h"
#include "Sphere.h"
#include "Interval.h"

#include <iostream>

FVector LightDirection(-0.7, 0.5, 1.0);
FVector L = LightDirection.GetSafeNormal();
double LightIntensity = 4.0;

double D_GGX(double a2, double NoH)
{
    double d = (NoH * a2 - NoH) * NoH + 1.0;
    return a2 / (PI * d * d);
}

double Vis_SmithJoint(double a2, double NoV, double NoL) 
{
    double Vis_SmithV = NoL * sqrt(NoV * (NoV - NoV * a2) + a2);
    double Vis_SmithL = NoV * sqrt(NoL * (NoL - NoL * a2) + a2);
    return 0.5 / (Vis_SmithV + Vis_SmithL);
}

FVector F_Schlick(FVector F0, FVector F90, double VoH)
{
    double Fc = Pow5(1 - VoH);
    return F90 * Fc + (1 - Fc) * F0;
}

FColor RayColor(const FRay& Ray, const IHittable& World)
{
    FHitRecord HitRecord;
    if (World.Hit(Ray, FInterval(0.001, Inf), HitRecord))
    {
        FVector N = HitRecord.Normal.GetSafeNormal();
        // return 0.5 * FColor(N.X + 1.0, N.Y + 1.0, N.Z + 1.0);
        FVector Pos = HitRecord.Point;
        
        FVector BaseColor(0.7, 0.7, 0.7);
        double Roughness = 0.5;
        double Metallic = 0.0;
        FVector F0 = Lerp(FVector(0.04, 0.04, 0.04), BaseColor, Metallic);
        FVector F90(1.0, 1.0, 1.0);

        FVector V = (-Ray.Direction).GetSafeNormal();
        FVector H = (L + V).GetSafeNormal();

        double a = Roughness * Roughness;
        double a2 = a * a;
        double NoH = Max(0.0, Dot(N, H));
        double NoV = Max(0.0, Dot(N, V));
        double NoL = Max(0.0, Dot(N, L));
        double VoH = Max(0.0, Dot(V, H));

        // Specular
        double D = D_GGX(a2, NoH);
        double Vis = Vis_SmithJoint(a2, NoV, NoL);
        FVector F = F_Schlick(F0, F90, VoH);

        FVector Specular = D * Vis * F;

        // Diffuse
        FVector kD = (1.0 - Metallic) * (FVector(1.0, 1.0, 1.0) - F);
        FVector Diffuse = BaseColor / PI;
        Diffuse *= kD;

        return (Diffuse + Specular) * LightIntensity * NoL;
    }

    double a = 0.5 * (Ray.Direction.Z + 1.0);
    return (1.0 - a) * FColor(1.0, 1.0, 1.0) + a * FColor(0.5, 0.7, 1.0);
}

int main()
{
    // Image
    double AspectRatio = 16.0 / 9.0;
    int ImageWidth = 1280;
    int ImageHeight = static_cast<int>(ImageWidth / AspectRatio);
    ImageHeight = ImageHeight < 1 ? 1 : ImageHeight;

    // World
    FHittableList World;
    World.Add(std::make_shared<FSphere>(FVector(1.0, 0.0, 0.0), 0.5));
    World.Add(std::make_shared<FSphere>(FVector(-1.0, 0.0, -100.5), 100.0));

    // Camera
    double FocalLength = 1.0;
    double ViewportHeight = 2.0;
    double ViewportWidth = ViewportHeight * (static_cast<double>(ImageWidth) / static_cast<double>(ImageHeight));
    FVector CameraCenter = FVector::ZeroVector;
    FVector CameraForward = FVector::ForwardVector;

    // Calculate the vectors across the horizontal and down the vertical viewport edges.
    FVector ViewportWorldU = FVector(0.0, ViewportWidth, 0.0);
    FVector ViewportWorldV = FVector(0.0, 0.0, -ViewportHeight);

    // Calculate the horizontal and vertical delta vectors from pixel to pixel.
    FVector PixelDeltaWorldU = ViewportWorldU / ImageWidth;
    FVector PixelDeltaWorldV = ViewportWorldV / ImageHeight;

    // Calculate the location of the upper left pixel.
    FVector ViewportUpperLeft = CameraCenter + CameraForward * FocalLength - ViewportWorldU * 0.5 - ViewportWorldV * 0.5;
    FVector Pixel00Location = ViewportUpperLeft + 0.5 * (PixelDeltaWorldU + PixelDeltaWorldV);

    // Render
    std::cout << "P3\n" << ImageWidth << ' ' << ImageHeight << "\n255\n";

    for (int j = 0; j < ImageHeight; j++)
    {
        std::clog << "\rScanlines remaining: " << (ImageHeight - j) << ' ' << std::flush;
        for (int i = 0; i < ImageWidth; i++)
        {
            FVector PixelCenterWorld = Pixel00Location + i * PixelDeltaWorldU + j * PixelDeltaWorldV;
            FVector RayDirection = PixelCenterWorld - CameraCenter;
            FRay Ray(CameraCenter, RayDirection.GetSafeNormal());

            FColor PixelColor = RayColor(Ray, World);
            WriteColor(std::cout, PixelColor);
        }
    }

    std::clog << "\rDone.                     \n";
}