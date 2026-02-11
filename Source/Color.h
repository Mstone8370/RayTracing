#pragma once

#include "Vector.h"

#include <iostream>
#include "Interval.h"

using FColor = FVector;

inline void WriteColor(std::ostream& Out, const FVector& PixelColor)
{
    static const FInterval Intensity(0.0, 0.999);
    int R = static_cast<int>(256 * Intensity.Clamp(PixelColor.X));
    int G = static_cast<int>(256 * Intensity.Clamp(PixelColor.Y));
    int B = static_cast<int>(256 * Intensity.Clamp(PixelColor.Z));

    Out << R << ' ' << G << ' ' << B << '\n';
}
