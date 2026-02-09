
#include "Vector.h"
#include "Color.h"
#include "Ray.h"
#include "Hittable.h"
#include "Sphere.h"

#include <iostream>

FColor RayColor(const FRay& Ray)
{
    FSphere Sphere(FVector(1.0, 0.0, 0.0), 0.5);
    
    FHitRecord HitRecord;
    if (Sphere.Hit(Ray, 0.001, std::numeric_limits<double>::infinity(), HitRecord))
    {
        FVector N = HitRecord.Normal;
        return 0.5 * FColor(N.X + 1.0, N.Y + 1.0, N.Z + 1.0);
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
            FRay Ray(CameraCenter, RayDirection.GetNormal());

            FColor PixelColor = RayColor(Ray);
            WriteColor(std::cout, PixelColor);
        }
    }

    std::clog << "\rDone.                     \n";
}