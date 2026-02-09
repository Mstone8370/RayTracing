#pragma once

#include <cmath>
#include <iostream>

class FVector
{
public:
    double X;
    double Y;
    double Z;

    static const FVector ZeroVector;
    static const FVector OneVector;
    static const FVector ForwardVector;
    static const FVector RightVector;
    static const FVector UpVector;
    
    constexpr FVector() : X(0.0) , Y(0.0) , Z(0.0) {}
    constexpr FVector(double InX, double InY, double InZ) : X(InX), Y(InY), Z(InZ) {}

    FVector operator-() const { return FVector(-X, -Y, -Z); }

    FVector operator+(double Value) const
    {
        return FVector(X + Value, Y + Value, Z + Value);
    }

    FVector& operator+=(const FVector& Other)
    {
        X += Other.X;
        Y += Other.Y;
        Z += Other.Z;
        return *this;
    }

    FVector& operator*=(double Scale)
    {
        X *= Scale;
        Y *= Scale;
        Z *= Scale;
        return *this;
    }

    FVector& operator/=(double Scale)
    {
        return *this *= 1.0 / Scale;
    }

    double Length() const
    {
        return std::sqrt(LengthSquared());
    }

    double LengthSquared() const
    {
        return X * X + Y * Y + Z * Z;
    }

    FVector GetNormal(double Tolerance = 1.e-8) const
    {
        const double SquaredLength = X * X + Y * Y + Z * Z;
        if (SquaredLength == 1.0)
        {
            return *this;
        }
        if (SquaredLength < Tolerance)
        {
            return FVector::ZeroVector;
        }

        const double Length = std::sqrt(SquaredLength);
        return FVector(X / Length, Y / Length, Z / Length);
    }

    void Normalize(double Tolerance = 1.e-8)
    {
        if (Length() < Tolerance)
        {
            *this = FVector::ZeroVector;
        }
        else
        {
            *this /= Length();
        }
    }
};

inline std::ostream& operator<<(std::ostream& Out, const FVector& Vec)
{
    return Out << Vec.X << ' ' << Vec.Y << ' ' << Vec.Z;
}

inline FVector operator+(const FVector& A, const FVector& B)
{
    return FVector(A.X + B.X, A.Y + B.Y, A.Z + B.Z);
}

inline FVector operator-(const FVector& A, const FVector& B)
{
    return FVector(A.X - B.X, A.Y - B.Y, A.Z - B.Z);
}

inline FVector operator*(const FVector& A, const FVector& B)
{
    return FVector(A.X * B.X, A.Y * B.Y, A.Z * B.Z);
}

inline FVector operator*(const FVector& Vec, double Scale)
{
    return FVector(Vec.X * Scale, Vec.Y * Scale, Vec.Z * Scale);
}

inline FVector operator*(double Scale, const FVector& Vec)
{
    return Vec * Scale;
}

inline FVector operator/(const FVector& Vec, double Scale)
{
    return FVector(Vec.X / Scale, Vec.Y / Scale, Vec.Z / Scale);
}

inline double Dot(const FVector& A, const FVector& B)
{
    return A.X * B.X + A.Y * B.Y + A.Z * B.Z;
}

inline FVector Cross(const FVector& A, const FVector& B)
{
    return FVector(
        A.Y * B.Z - A.Z * B.Y,
        A.Z * B.X - A.X * B.Z,
        A.X * B.Y - A.Y * B.X
    );
}
