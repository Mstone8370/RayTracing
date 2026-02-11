#pragma once

#include "Hittable.h"
#include "Color.h"
#include "Ray.h"

class FCamera
{
public:
    FCamera()
        : AspectRatio(16.0 / 9.0)
        , ImageWidth(640)
        , ImageHeight(360)
        , SamplesPerPixel(10)
        , PixelSampleScale(0.1)
        , Location(FVector::ZeroVector)
        , Direction(FVector::ForwardVector)
        , Pixel00Location(FVector::ZeroVector)
        , PixelDeltaU(FVector::ZeroVector)
        , PixelDeltaV(FVector::ZeroVector)
    {}

    FCamera(double InAspectRatio, int InImageWidth)
        : AspectRatio(InAspectRatio)
        , ImageWidth(InImageWidth)
        , ImageHeight(static_cast<int>(InImageWidth / InAspectRatio))
        , SamplesPerPixel(10)
        , PixelSampleScale(0.1)
        , Location(FVector::ZeroVector)
        , Direction(FVector::ForwardVector)
        , Pixel00Location(FVector::ZeroVector)
        , PixelDeltaU(FVector::ZeroVector)
        , PixelDeltaV(FVector::ZeroVector)
    {}
    
    void Render(const IHittable& World);

    double GetAspectRatio() const { return AspectRatio; }
    int GetImageWidth() const { return ImageWidth; }
    int GetImageHeight() const { return ImageHeight; }
    int GetSamplesPerPixel() const { return SamplesPerPixel; }
    FVector GetLocation() const { return Location; }
    FVector GetDirection() const { return Direction; }

    void SetAspectRatio(double InAspectRatio);
    void SetImageWidth(int InImageWidth);
    void SetSamplesPerPixel(int InSamplesPerPixel);
    void SetLocation(const FVector& InLocation);
    void SetDirection(const FVector& InDirection);

private:
    void Initialize();

    FColor RayColor(const FRay& Ray, const IHittable& World) const;

    FRay GetRay(int PixelX, int PixelY) const;

    FVector SampleSquare() const;
    
    double AspectRatio;
    
    int ImageWidth;
    int ImageHeight;

    int SamplesPerPixel;
    double PixelSampleScale;

    FVector Location;
    FVector Direction;

    FVector Pixel00Location;
    FVector PixelDeltaU;
    FVector PixelDeltaV;
};
