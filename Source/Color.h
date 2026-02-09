#pragma once

#include "Vector.h"

#include <iostream>

using FColor = FVector;

void WriteColor(std::ostream& Out, const FVector& PixelColor)
{
    int R = static_cast<int>(255.999 * PixelColor.X);
    int G = static_cast<int>(255.999 * PixelColor.Y);
    int B = static_cast<int>(255.999 * PixelColor.Z);

    Out << R << ' ' << G << ' ' << B << '\n';
}