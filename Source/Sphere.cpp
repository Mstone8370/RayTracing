#include "Sphere.h"

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

    double SquaredDiscriminant = std::sqrt(Discriminant);

    double T = (h - SquaredDiscriminant) / a;
    if (T <= TMin || T >= TMax)
    {
        T = (h + SquaredDiscriminant) / a;
        if (T <= TMin || T >= TMax)
        {
            return false;
        }
    }

    OutHitRecord.T = T;
    OutHitRecord.Point = Ray.At(T);
    OutHitRecord.Normal = (OutHitRecord.Point - Location) / Radius;

    return true;
}
