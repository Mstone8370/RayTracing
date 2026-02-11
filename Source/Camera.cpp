#include "Camera.h"

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
    double Fc = FMath::Pow5(1 - VoH);
    return F90 * Fc + (1 - Fc) * F0;
}


void FCamera::Render(const IHittable &World)
{
    Initialize();

    std::cout << "P3\n" << ImageWidth << ' ' << ImageHeight << "\n255\n";
    for (int PixelY = 0; PixelY < ImageHeight; ++PixelY)
    {
        std::clog << "\rScanlines remaining: " << (ImageHeight - PixelY) << ' ' << std::flush;
        for (int PixelX = 0; PixelX < ImageWidth; ++PixelX)
        {
            FColor PixelColor(0.0, 0.0, 0.0);
            for (int Sample = 0; Sample < SamplesPerPixel; ++Sample)
            {
                FRay Ray = GetRay(PixelX, PixelY);
                PixelColor += RayColor(Ray, World);
            }
            WriteColor(std::cout, PixelColor * PixelSampleScale);
        }
    }

    std::clog << "\rDone.                     \n";
}

void FCamera::SetAspectRatio(double InAspectRatio)
{
    if (InAspectRatio > 1.e-8)
    {
        AspectRatio = InAspectRatio;
    
        Initialize();
    }
}

void FCamera::SetImageWidth(int InImageWitdh)
{
    if (InImageWitdh > 0)
    {
        ImageWidth = InImageWitdh;
    
        Initialize();
    }
}

void FCamera::SetSamplesPerPixel(int InSamplesPerPixel)
{
    if (InSamplesPerPixel > 0)
    {
        SamplesPerPixel = InSamplesPerPixel;

        Initialize();
    }
}

void FCamera::SetLocation(const FVector &InLocation)
{
    Location = InLocation;

    Initialize();
}

void FCamera::SetDirection(const FVector &InDirection)
{
    Direction = InDirection;

    Initialize();
}

void FCamera::Initialize()
{
    ImageHeight = static_cast<int>(ImageWidth / AspectRatio);
    ImageHeight = ImageHeight < 1 ? 1 : ImageHeight;

    PixelSampleScale = 1.0 / static_cast<double>(SamplesPerPixel);

    Location = FVector::ZeroVector;
    Direction = FVector::ForwardVector;

    // Determine viewport dimensions.
    double FocalLength = 1.0;
    double ViewportHeight = 2.0;
    double ViewportWidth = ViewportHeight * (static_cast<double>(ImageWidth) / static_cast<double>(ImageHeight));

    // Calculate the vectors across the horizontal and down the vertical viewport edges.
    FVector ViewportU = FVector(0.0, ViewportWidth, 0.0);
    FVector ViewportV = FVector(0.0, 0.0, -ViewportHeight);

    // Calculate the horizontal and vertical delta vectors from pixel to pixel.
    PixelDeltaU = ViewportU / ImageWidth;
    PixelDeltaV = ViewportV / ImageHeight;

    // Calculate the location of the upper left pixel.
    FVector ViewportUpperLeft = Location + FocalLength * Direction - ViewportU * 0.5 - ViewportV * 0.5;
    Pixel00Location = ViewportUpperLeft + 0.5 * (PixelDeltaU + PixelDeltaV);
}

FColor FCamera::RayColor(const FRay &Ray, const IHittable& World, int Depth) const
{
    if (Depth >= MaxDepth)
    {
        return FColor(0.0, 0.0, 0.0);
    }

    FHitRecord HitRecord;
    if (World.Hit(Ray, FInterval(0.001, Inf), HitRecord))
    {
        // FVector NewDirection = FMath::RandomUnitVectorOnHemisphere(HitRecord.Normal);
        FVector NewDirection = HitRecord.Normal + FMath::RandomUnitVector();
        return 0.5 * RayColor(FRay(HitRecord.Point, NewDirection), World, Depth + 1); // Grey diffuse
    }

    double a = 0.5 * (Ray.Direction.Z + 1.0);
    return (1.0 - a) * FColor(1.0, 1.0, 1.0) + a * FColor(0.5, 0.7, 1.0);
}

FRay FCamera::GetRay(int PixelX, int PixelY) const
{
    FVector Offset = SampleSquare();
    FVector PixelSample = Pixel00Location +
        (static_cast<double>(PixelX) + Offset.X) * PixelDeltaU +
        (static_cast<double>(PixelY) + Offset.Y) * PixelDeltaV;

    FVector RayOrigin = Location;
    FVector RayDirection = (PixelSample - RayOrigin).GetSafeNormal();
    
    return FRay(RayOrigin, RayDirection);
}

FVector FCamera::SampleSquare() const
{
    if (SamplesPerPixel == 1)
    {
        return FVector(0.5, 0.5, 0.0);
    }
    return FVector(FMath::RandomDouble() - 0.5, FMath::RandomDouble() - 0.5, 0.0);
}
