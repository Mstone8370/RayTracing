#pragma once

#include "Hittable.h"
#include "Color.h"
#include "Ray.h"

class FCamera
{
public:
    FCamera()
        : AspectRatio(16.0 / 9.0)
        , VerticalFov(90.0)
        , ImageWidth(640)
        , ImageHeight(360)
        , SamplesPerPixel(10)
        , PixelSampleScale(0.1)
        , MaxDepth(10)
        , DefocusAngle(0.0)
        , FocusDistance(10.0)
        , Location(FVector::ZeroVector)
        , LookAt(FVector::ForwardVector)
        , Pixel00Location(FVector::ZeroVector)
        , PixelDeltaU(FVector::ZeroVector)
        , PixelDeltaV(FVector::ZeroVector)
    {}

    FCamera(double InAspectRatio, int InImageWidth)
        : AspectRatio(InAspectRatio)
        , VerticalFov(90.0)
        , ImageWidth(InImageWidth)
        , ImageHeight(static_cast<int>(InImageWidth / InAspectRatio))
        , SamplesPerPixel(10)
        , PixelSampleScale(0.1)
        , MaxDepth(10)
        , DefocusAngle(0.0)
        , FocusDistance(10.0)
        , Location(FVector::ZeroVector)
        , LookAt(FVector::ForwardVector)
        , Pixel00Location(FVector::ZeroVector)
        , PixelDeltaU(FVector::ZeroVector)
        , PixelDeltaV(FVector::ZeroVector)
    {}
    
    void Render(const IHittable& World);

    double GetAspectRatio() const { return AspectRatio; }
    double GetVerticalFov() const { return VerticalFov; }
    int GetImageWidth() const { return ImageWidth; }
    int GetImageHeight() const { return ImageHeight; }
    int GetSamplesPerPixel() const { return SamplesPerPixel; }
    int GetMaxDepth() const { return MaxDepth; }
    double GetDefocusAngle() const { return DefocusAngle; }
    double GetFocusDistance() const { return FocusDistance; }
    FVector GetLocation() const { return Location; }
    FVector GetLookAt() const { return LookAt; }

    void SetAspectRatio(double InAspectRatio);
    void SetVerticalFov(double InVerticalFov);
    void SetImageWidth(int InImageWidth);
    void SetSamplesPerPixel(int InSamplesPerPixel);
    void SetMaxDepth(int InMaxDepth) { MaxDepth = InMaxDepth; }
    void SetDefocusAngle(double InDefocusAngle);
    void SetFocusDistance(double InFocusDistance);
    void SetLocation(const FVector& InLocation);
    void SetLookAt(const FVector& InLookAt);

private:
    void Initialize();

    FColor RayColor(const FRay& Ray, const IHittable& World, int Depth = 0) const;

    FRay GetRay(int PixelX, int PixelY) const;

    FVector DefocusDistSample() const;

    FVector SampleSquare() const;
    
    double AspectRatio;

    double VerticalFov;
    
    int ImageWidth;
    int ImageHeight;

    int SamplesPerPixel;
    double PixelSampleScale;
    int MaxDepth;

    double DefocusAngle;
    double FocusDistance;

    FVector Location;
    FVector LookAt;

    FVector Pixel00Location;
    FVector PixelDeltaU;
    FVector PixelDeltaV;

    FVector DefocusDiskU;
    FVector DefocusDiskV;
};
