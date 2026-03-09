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
    {
        const FVector Extent = FVector(Radius, Radius, Radius);
        BBox = FAABB(StartLocation - Extent, StartLocation + Extent);
    }

    FSphere(const FVector& InStartLocation, const FVector& InEndLocation, double InRadius, std::shared_ptr<IMaterial> InMaterial)
        : StartLocation(InStartLocation)
        , EndLocation(InEndLocation)
        , bIsMoving(true)
        , Radius(FMath::Max(0.0, InRadius))
        , Material(InMaterial)
    {
        const FVector Extent = FVector(Radius, Radius, Radius);
        FAABB Box1(StartLocation - Extent, StartLocation + Extent);
        FAABB Box2(EndLocation - Extent, EndLocation + Extent);
        BBox = FAABB(Box1, Box2);
    }

    virtual bool Hit(const FRay& Ray, const FInterval& Interval, FHitRecord& OutHitRecord) const override;

    virtual FAABB BoundingBox() const override { return BBox; }

    FVector GetLocation(double Time = 0.0) const;
    double GetRadius() const { return Radius; }

protected:
    FVector StartLocation;
    FVector EndLocation;
    bool bIsMoving;
    double Radius;
    FAABB BBox;
    
    std::shared_ptr<IMaterial> Material;

    static void GetSphereUV(const FVector& P, double& OutU, double& OutV)
    {
        /**
         * P: A given point on the sphere of radius one, centered at the origin.
         * OutU: Returned value [0, 1] of angle around the Z axis from X = -1.
         * OutV: Returned value [0, 1] of angle from Z = +1 to Z = -1.
         */

        double Phi = std::atan2(P.Y, -P.X);
        double Theta = std::acos(P.Z);

        OutU = Phi / (2 * PI);
        OutV = Theta / PI;
    }
};