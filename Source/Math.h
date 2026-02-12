#pragma once

#include <limits>
#include <cmath>
#include <random>
#include "Vector.h"

constexpr double Inf = std::numeric_limits<double>::infinity();
constexpr double PI = 3.1415926535897932385;

struct FMath
{
    // Angle conversion
    static double DegreesToRadians(double Degrees);
    static double RadiansToDegrees(double Radians);

    // Power and square root
    static double Pow(double Base, double Exponent);
    static double Pow5(double X);
    static double Sqrt(double X);

    // Random number generation
    static double RandomDouble();
    static double RandomDouble(double Min, double Max);

    // Random vector generation
    static FVector RandomVector();
    static FVector RandomVector(double Min, double Max);
    static FVector RandomUnitVector();
    static FVector RandomUnitVectorOnHemisphere(const FVector& Normal);

    // Comparison and utility
    static bool IsNearlyZero(double Value, double Tolerance = 1.e-8);
    static bool IsNearlyZero(const FVector& V, double Tolerance = 1.e-8);
    static double Abs(double Value);

    // Template functions (must be defined in header)
    template<typename T>
    static T Max(const T& A, const T& B)
    {
        return (A > B) ? A : B;
    }

    template<typename T>
    static T Min(const T& A, const T& B)
    {
        return (A < B) ? A : B;
    }

    template<typename T>
    static T Clamp(const T& Value, const T& MinValue, const T& MaxValue)
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
    static T Lerp(const T& A, const T& B, double R)
    {
        return A + (B - A) * R;
    }

    // Vector operations
    static FVector Reflect(const FVector& V, const FVector& Normal);
    static FVector Refract(const FVector& V, const FVector& Normal, double EtaRatio);
};