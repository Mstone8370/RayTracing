#pragma once

#include "Hittable.h"
#include "Math.h"

class IMaterial;

class FSphere : public IHittable
{
public:
    FSphere(const FVector& InStaticLocation, double InRadius, std::shared_ptr<IMaterial> InMaterial)
        : StartLocation(InStaticLocation)
        , EndLocation(InStaticLocation)
        , bIsMoving(false)
        , Radius(FMath::Max(0.0, InRadius))
        , Material(InMaterial)
    {}

    FSphere(const FVector& InStartLocation, const FVector& InEndLocation, double InRadius, std::shared_ptr<IMaterial> InMaterial)
        : StartLocation(InStartLocation)
        , EndLocation(InEndLocation)
        , bIsMoving(true)
        , Radius(FMath::Max(0.0, InRadius))
        , Material(InMaterial)
    {}

    virtual bool Hit(const FRay& Ray, const FInterval& Interval, FHitRecord& OutHitRecord) const override;

    FVector GetLocation(double Time = 0.0) const;
    double GetRadius() const { return Radius; }

protected:
    FVector StartLocation;
    FVector EndLocation;
    bool bIsMoving;
    double Radius;
    
    std::shared_ptr<IMaterial> Material;
};