#pragma once

#include "Vector.h"

#include <iostream>
#include "Interval.h"
#include "Math.h"

using FColor = FVector;

inline double LinearToSRGB(double Linear)
{
    if (Linear <= 0.0031308)
    {
        return 12.92 * Linear;
    }
    else
    {
        return 1.055 * FMath::Pow(Linear, 1.0 / 2.4) - 0.055;
    }
}

inline double SRGBToLinear(double SRGB)
{
    if (SRGB <= 0.04045)
    {
        return SRGB / 12.92;
    }
    else
    {
        return FMath::Pow((SRGB + 0.055) / 1.055, 2.4);
    }
}

inline FVector LinearToSRGB(const FVector& LinearColor)
{
    return FVector(
        LinearToSRGB(LinearColor.X),
        LinearToSRGB(LinearColor.Y),
        LinearToSRGB(LinearColor.Z)
    );
}

inline FVector SRGBToLinear(const FVector& SRGBColor)
{
    return FVector(
        SRGBToLinear(SRGBColor.X),
        SRGBToLinear(SRGBColor.Y),
        SRGBToLinear(SRGBColor.Z)
    );
}

inline void WriteColor(std::ostream& Out, const FVector& PixelColor)
{
    FVector SRGBColor = LinearToSRGB(PixelColor);
    
    static const FInterval Intensity(0.0, 0.999);
    int R = static_cast<int>(256 * Intensity.Clamp(SRGBColor.X));
    int G = static_cast<int>(256 * Intensity.Clamp(SRGBColor.Y));
    int B = static_cast<int>(256 * Intensity.Clamp(SRGBColor.Z));

    Out << R << ' ' << G << ' ' << B << '\n';
}
