#pragma once

#include "Vector.h"
#include "Ray.h"
#include "Interval.h"
#include "AABB.h"

class IMaterial;

struct FHitRecord
{
    FVector HitLocation = FVector::ZeroVector;
    FVector Normal = FVector::ForwardVector;
    double HitT = 0.0;
    double U = 0.0;
    double V = 0.0;
    bool bFrontFace = false;
    std::shared_ptr<IMaterial> Material = nullptr;

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
    
    virtual bool Hit(const FRay& Ray, const FInterval& Interval, FHitRecord& OutHitRecord) const = 0;

    virtual FAABB BoundingBox() const = 0; // Empty Bounding Box
};