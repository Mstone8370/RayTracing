#pragma once

#include "Hittable.h"

class FSphere : public IHittable
{
public:
    FSphere(const FVector& InCenter, double InRadius)
        : Location(InCenter)
        , Radius(std::fmax(0.0, InRadius))
    {}

    virtual bool Hit(const FRay& Ray, double TMin, double TMax, FHitRecord& OutHitRecord) const override;

    FVector GetLocation() const { return Location; }
    double GetRadius() const { return Radius; }

protected:
    FVector Location;
    double Radius;
};