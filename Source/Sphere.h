#pragma once

#include "Hittable.h"

class FSphere : public FHittable
{
public:
    FSphere(const FVector& InCenter, double InRadius)
        : FHittable(InCenter)
        , Radius(std::fmax(0.0, InRadius))
    {}

    virtual bool Hit(const FRay& Ray, double TMin, double TMax, FHitRecord& OutHitRecord) const override;

protected:
    double Radius;
};