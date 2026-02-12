#include "Math.h"

double FMath::DegreesToRadians(double Degrees)
{
    return Degrees * PI / 180.0;
}

double FMath::RadiansToDegrees(double Radians)
{
    return Radians * 180.0 / PI;
}

double FMath::Pow(double Base, double Exponent)
{
    return std::pow(Base, Exponent);
}

double FMath::Pow5(double X)
{
    return X * X * X * X * X;
}

double FMath::Sqrt(double X)
{
    return std::sqrt(X);
}

double FMath::RandomDouble()
{
    static std::uniform_real_distribution<double> Distribution(0.0, 1.0);
    static std::mt19937 Generator;
    return Distribution(Generator);
}

double FMath::RandomDouble(double Min, double Max)
{
    return Min + (Max - Min) * RandomDouble();
}

FVector FMath::RandomVector()
{
    return FVector(RandomDouble(), RandomDouble(), RandomDouble());
}

FVector FMath::RandomVector(double Min, double Max)
{
    return FVector(RandomDouble(Min, Max), RandomDouble(Min, Max), RandomDouble(Min, Max));
}

FVector FMath::RandomUnitVector()
{
    while (true)
    {
        const FVector V = RandomVector(-1.0, 1.0);
        const double SquaredLength = V.LengthSquared();
        if (1e-16 < SquaredLength && SquaredLength <= 1.0)
        {
            return V.GetSafeNormal();
        }
    }
}

FVector FMath::RandomUnitVectorOnHemisphere(const FVector& Normal)
{
    const FVector OnUnitSphere = RandomUnitVector();
    if (Dot(OnUnitSphere, Normal) > 0.0)
    {
        return OnUnitSphere;
    }
    else
    {
        return -OnUnitSphere;
    }
}

bool FMath::IsNearlyZero(double Value, double Tolerance)
{
    return std::abs(Value) <= Tolerance;
}

bool FMath::IsNearlyZero(const FVector& V, double Tolerance)
{
    return IsNearlyZero(V.X, Tolerance) && IsNearlyZero(V.Y, Tolerance) && IsNearlyZero(V.Z, Tolerance);
}

double FMath::Abs(double Value)
{
    return std::abs(Value);
}

FVector FMath::Reflect(const FVector& V, const FVector& Normal)
{
    return V - 2.0 * Dot(V, Normal) * Normal;
}

FVector FMath::Refract(const FVector& V, const FVector& Normal, double EtaRatio)
{
    double CosTheta = FMath::Min(Dot(-V, Normal), 1.0);
    FVector Perpendicular = EtaRatio * (V + CosTheta * Normal);
    FVector Parallel = -FMath::Sqrt(FMath::Abs(1.0 - Perpendicular.LengthSquared())) * Normal;
    return Perpendicular + Parallel;
}
