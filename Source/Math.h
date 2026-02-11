#pragma once

#include <limits>
#include <cmath>
#include <random>
#include "Vector.h"

constexpr double Inf = std::numeric_limits<double>::infinity();
constexpr double PI = 3.1415926535897932385;

namespace FMath
{
    inline double DegreesToRadians(double Degrees)
    {
        return Degrees * PI / 180.0;
    }

    inline double RadiansToDegrees(double Radians)
    {
        return Radians * 180.0 / PI;
    }

    inline double Pow(double Base, double Exponent)
    {
        return std::pow(Base, Exponent);
    }

    inline double Pow5(double X)
    {
        return X * X * X * X * X;
    }

    inline double Sqrt(double X)
    {
        return std::sqrt(X);
    }

    inline double RandomDouble()
    {
        static std::uniform_real_distribution<double> Distribution(0.0, 1.0);
        static std::mt19937 Generator;
        return Distribution(Generator);
    }

    inline double RandomDouble(double Min, double Max)
    {
        return Min + (Max - Min) * RandomDouble();
    }

    inline FVector RandomVector()
    {
        return FVector(RandomDouble(), RandomDouble(), RandomDouble());
    }

    inline FVector RandomVector(double Min, double Max)
    {
        return FVector(RandomDouble(Min, Max), RandomDouble(Min, Max), RandomDouble(Min, Max));
    }

    inline FVector RandomUnitVector()
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

    inline FVector RandomUnitVectorOnHemisphere(const FVector& Normal)
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

    template<typename T>
    inline T Max(const T& A, const T& B)
    {
        return (A > B) ? A : B;
    }

    template<typename T>
    inline T Min(const T& A, const T& B)
    {
        return (A < B) ? A : B;
    }

    template<typename T>
    inline T Clamp(const T& Value, const T& MinValue, const T& MaxValue)
    {
        if (Value < MinValue)
        {
            return MinValue;
        }
        else if (Value > MaxValue)
        {
            return MaxValue;
        }
        return Value;
    }

    template<typename T>
    inline T Lerp(const T& A, const T& B, double R)
    {
        return A + (B - A) * R;
    }
}