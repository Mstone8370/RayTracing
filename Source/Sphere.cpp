#include "Sphere.h"

#include "Math.h"
#include "Ray.h"

bool FSphere::Hit(const FRay& Ray, const FInterval& Interval, FHitRecord& OutHitRecord) const
{
    FVector ToSphere = Location - Ray.Origin;

    double a = Ray.Direction.LengthSquared();
    double h = Dot(Ray.Direction, ToSphere);
    double c = ToSphere.LengthSquared() - Radius * Radius;
    
    double Discriminant = h * h - a * c;
    if (Discriminant < 0.0)
    {
        return false;
    }

    double SquaredDiscriminant = Sqrt(Discriminant);

    double HitT = (h - SquaredDiscriminant) / a;
    if (!Interval.Surrounds(HitT))
    {
        HitT = (h + SquaredDiscriminant) / a;
        if (!Interval.Surrounds(HitT))
        {
            return false;
        }
    }

    OutHitRecord.HitT = HitT;
    OutHitRecord.Point = Ray.At(HitT);
    FVector OutwardNormal = (OutHitRecord.Point - Location) / Radius;
    OutHitRecord.SetFaceNormal(Ray, OutwardNormal);

    return true;
}
