#pragma once

#include "Vector.h"

class FRay
{
public:
    FVector Origin;
    FVector Direction;

    FRay()
        : Origin(FVector::ZeroVector)
        , Direction(FVector::ForwardVector)
    {}

    FRay(const FVector& InOrigin, const FVector& InDirection)
        : Origin(InOrigin)
        , Direction(InDirection.GetNormal())
    {}

    FVector At(double T) const
    {
        return Origin + Direction * T;
    }
};
