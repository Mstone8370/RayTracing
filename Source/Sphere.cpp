#include "Sphere.h"

#include "Math.h"
#include "Ray.h"

bool FSphere::Hit(const FRay& Ray, double TMin, double TMax, FHitRecord& OutHitRecord) const
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

    double T = (h - SquaredDiscriminant) / a;
    if (T <= TMin || T >= TMax)
    {
        T = (h + SquaredDiscriminant) / a;
        if (T <= TMin || T >= TMax)
        {
            return false;
        }
    }

    OutHitRecord.HitT = T;
    OutHitRecord.Point = Ray.At(T);
    FVector OutwardNormal = (OutHitRecord.Point - Location) / Radius;
    OutHitRecord.SetFaceNormal(Ray, OutwardNormal);

    return true;
}
