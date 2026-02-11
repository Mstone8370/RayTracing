#pragma once

#include "Math.h"

class FInterval
{
public:
    double Min;
    double Max;

    FInterval()
        : Min(Inf)
        , Max(-Inf)
    {}

    FInterval(double InMin, double InMax)
        : Min(InMin)
        , Max(InMax)
    {}

    double Size() const { return Max - Min; }

    bool Contains(double X) const
    {
        return Min <= X && X <= Max;
    }

    bool Surrounds(double X) const
    {
        return Min < X && X < Max;
    }

    double Clamp(double X) const
    {
        return FMath::Clamp(X, Min, Max);
    }

    static const FInterval Empty;
    static const FInterval Universe;
};