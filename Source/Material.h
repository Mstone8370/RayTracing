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


class FLambertian : public IMaterial
{
public:
    FLambertian(const FVector& InAlbedo)
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
        
        OutScatteredRay = FRay(HitRecord.HitLocation, ScatterDirection.GetSafeNormal());
        OutAttenuation = Albedo;
        
        return true;
    }
};


class FMetal : public IMaterial
{
public:
    FMetal(const FVector& InAlbedo, double InFuzziness = 0.0)
        : IMaterial(InAlbedo)
        , Fuzziness(FMath::Clamp(InFuzziness, 0.0, 1.0))
    {}

    virtual bool Scatter(const FRay& InRay, const FHitRecord& HitRecord, FVector& OutAttenuation, FRay& OutScatteredRay) const override
    {
        FVector ReflectedDirection = FMath::Reflect(InRay.Direction, HitRecord.Normal);
        ReflectedDirection += Fuzziness * FMath::RandomUnitVector();
        
        OutScatteredRay = FRay(HitRecord.HitLocation, ReflectedDirection.GetSafeNormal());
        OutAttenuation = Albedo;
        
        return Dot(OutScatteredRay.Direction, HitRecord.Normal) > 0.0;
    }

protected:
    double Fuzziness;
};

class FDielectric : public IMaterial
{
public:
    FDielectric(double InRefrationIndex)
        : IMaterial(FVector(1.0, 1.0, 1.0))
        , RefrationIndex(InRefrationIndex)
    {}

    virtual bool Scatter(const FRay& InRay, const FHitRecord& HitRecord, FVector& OutAttenuation, FRay& OutScatteredRay) const override
    {
        OutAttenuation = Albedo;
        double EtaRatio = HitRecord.bFrontFace ? (1.0 / RefrationIndex) : RefrationIndex;

        FVector UnitDirection = InRay.Direction.GetSafeNormal();

        double CosTheta = FMath::Min(Dot(-UnitDirection, HitRecord.Normal), 1.0);
        double SinTheta = FMath::Sqrt(1.0 - CosTheta * CosTheta);

        bool bCannotRefract = EtaRatio * SinTheta > 1.0;
        FVector Direction;
        if (bCannotRefract || Reflectance(CosTheta, EtaRatio) > FMath::RandomDouble())
        {
            Direction = FMath::Reflect(UnitDirection, HitRecord.Normal);
        }
        else
        {
            Direction = FMath::Refract(UnitDirection, HitRecord.Normal, EtaRatio);
        }

        OutScatteredRay = FRay(HitRecord.HitLocation, Direction);
        
        return true;
    }

protected:
    double RefrationIndex;

    static double Reflectance(double Cosine, double RefrationIdex)
    {
        double R0 = (1 - RefrationIdex) / (1 + RefrationIdex);
        R0 = R0 * R0;
        return R0 + (1 - R0) * FMath::Pow5(1 - Cosine);
    }
};
