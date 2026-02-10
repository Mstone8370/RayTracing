#include "Vector.h"

const FVector FVector::ZeroVector(0.0, 0.0, 0.0);
const FVector FVector::OneVector(1.0, 1.0, 1.0);
const FVector FVector::ForwardVector(1.0, 0.0, 0.0);
const FVector FVector::RightVector(0.0, 1.0, 0.0);
const FVector FVector::UpVector(0.0, 0.0, 1.0);

// Static member functions
double FVector::Distance(const FVector& A, const FVector& B)
{
    return (A - B).Length();
}

double FVector::DistanceSquared(const FVector& A, const FVector& B)
{
    return (A - B).LengthSquared();
}

FVector FVector::Lerp(const FVector& A, const FVector& B, double T)
{
    return A + (B - A) * T;
}
