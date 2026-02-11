#pragma once

#include "Hittable.h"
#include "Ray.h"
#include "Vector.h"
#include "Math.h"

class IMaterial
{
public:
    IMaterial()
        : Albedo(FVector(0.5, 0.5, 0.5))
    {}

    IMaterial(const FVector& InAlbedo)
        : Albedo(InAlbedo)
    {}

    virtual ~IMaterial() = default;

    virtual bool Scatter(const FRay& InRay, const FHitRecord& HitRecord, FVector& OutAttenuation, FRay& OutScatteredRay) const = 0;
    
protected:
    FVector Albedo;
};


class MLambertian : public IMaterial
{
public:
    MLambertian(const FVector& InAlbedo)
        : IMaterial(InAlbedo)
    {}

    virtual bool Scatter(const FRay& InRay, const FHitRecord& HitRecord, FVector& OutAttenuation, FRay& OutScatteredRay) const override
    {
        FVector ScatterDirection = HitRecord.Normal + FMath::RandomUnitVector();

        // Catch degenerate scatter direction
        if (FMath::IsNearlyZero(ScatterDirection))
        {
            ScatterDirection = HitRecord.Normal;
        }
        
        OutScatteredRay = FRay(HitRecord.HitLocation, ScatterDirection);
        OutAttenuation = Albedo;
        
        return true;
    }
};


class MMetal : public IMaterial
{
public:
    MMetal(const FVector& InAlbedo)
        : IMaterial(InAlbedo)
    {}

    virtual bool Scatter(const FRay& InRay, const FHitRecord& HitRecord, FVector& OutAttenuation, FRay& OutScatteredRay) const override
    {
        FVector ScatterDirection = FMath::Reflect(InRay.Direction, HitRecord.Normal);
        
        OutScatteredRay = FRay(HitRecord.HitLocation, ScatterDirection);
        OutAttenuation = Albedo;
        
        return true;
    }
};
