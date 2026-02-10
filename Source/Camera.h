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
    {}

    FCamera(double InAspectRadio, int InImageWidth)
        : AspectRatio(InAspectRadio)
        , ImageWidth(InImageWidth)
    {}
    
    void Render(const IHittable& World);

    double GetAspectRatio() const { return AspectRatio; }
    int GetImageWidth() const { return ImageWidth; }
    int GetImageHeight() const { return ImageHeight; }
    FVector GetLocation() const { return Location; }
    FVector GetDirection() const { return Direction; }

    void SetAspectRatio(double InAspectRatio);
    void SetImageWidth(int InImageWitdh);
    void SetLocation(const FVector& InLocation);
    void SetDirection(const FVector& InDirection);

private:
    void Initialize();

    FColor RayColor(const FRay& Ray, const IHittable& World) const;
    
    double AspectRatio;
    
    int ImageWidth;
    int ImageHeight;

    FVector Location;
    FVector Direction;

    FVector Pixel00Location;
    FVector PixelDeltaU;
    FVector PixelDeltaV;
};
