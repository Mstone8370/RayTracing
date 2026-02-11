#pragma once

#include "Hittable.h"
#include "Math.h"

class IMaterial;

class FSphere : public IHittable
{
public:
    FSphere(const FVector& InLocation, double InRadius, std::shared_ptr<IMaterial> InMaterial)
        : Location(InLocation)
        , Radius(FMath::Max(0.0, InRadius))
        , Material(InMaterial)
    {}

    virtual bool Hit(const FRay& Ray, const FInterval& Interval, FHitRecord& OutHitRecord) const override;

    FVector GetLocation() const { return Location; }
    double GetRadius() const { return Radius; }

protected:
    FVector Location;
    double Radius;
    
    std::shared_ptr<IMaterial> Material;
};