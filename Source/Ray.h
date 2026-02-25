#pragma once

#include "Vector.h"

class FRay
{
public:
    FVector Origin;
    FVector Direction;
    double Time;

    FRay()
        : Origin(FVector::ZeroVector)
        , Direction(FVector::ForwardVector)
        , Time(0.0)
    {}

    FRay(const FVector& InOrigin, const FVector& InDirection, double InTime = 0.0)
        : Origin(InOrigin)
        , Direction(InDirection.GetSafeNormal())
        , Time(InTime)
    {}

    FVector At(double T) const
    {
        return Origin + Direction * T;
    }
};
