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

    FInterval(const FInterval& A, const FInterval& B)
        : Min(FMath::Min(A.Min, B.Min))
        , Max(FMath::Max(A.Max, B.Max))
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

    FInterval Expand(double Delta) const
    {
        const double Padding = Delta / 2.0;
        return FInterval(Min - Padding, Max + Padding);
    }

    static const FInterval Empty;
    static const FInterval Universe;
};