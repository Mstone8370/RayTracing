#pragma once

#include "Vector.h"
#include "Ray.h"

struct FHitRecord
{
    FVector Point = FVector::ZeroVector;
    FVector Normal = FVector::ForwardVector;
    double HitT = 0.0;
    bool bFrontFace = false;

    void SetFaceNormal(const FRay& Ray, const FVector& OutwardNormal)
    {
        bFrontFace = Dot(Ray.Direction, OutwardNormal) < 0.0;
        Normal = bFrontFace ? OutwardNormal : -OutwardNormal;
    }
};

class IHittable
{
public:
    virtual ~IHittable() = default;
    
    virtual bool Hit(const FRay& Ray, double TMin, double TMax, FHitRecord& OutHitRecord) const = 0;
};