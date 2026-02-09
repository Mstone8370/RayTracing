#pragma once

#include "Vector.h"

class FRay;

struct FHitRecord
{
    FVector Point = FVector::ZeroVector;
    FVector Normal = FVector::ForwardVector;
    double HitT = 0.0;
};

class FHittable
{
public:
    FHittable() : Location(FVector::ZeroVector) {}
    FHittable(const FVector& InLocation) : Location(InLocation) {}

    virtual ~FHittable() = default;
    
    virtual bool Hit(const FRay& Ray, double TMin, double TMax, FHitRecord& OutHitRecord) const = 0;

protected:
    FVector Location;
};