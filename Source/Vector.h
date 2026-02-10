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

    // Unary operators
    FVector operator-() const { return FVector(-X, -Y, -Z); }

    // Comparison operators
    constexpr bool operator==(const FVector& Other) const
    {
        return X == Other.X && Y == Other.Y && Z == Other.Z;
    }

    constexpr bool operator!=(const FVector& Other) const
    {
        return !(*this == Other);
    }

    bool Equals(const FVector& Other, double Tolerance = 1.e-8) const
    {
        return std::abs(X - Other.X) <= Tolerance
            && std::abs(Y - Other.Y) <= Tolerance
            && std::abs(Z - Other.Z) <= Tolerance;
    }

    // Scalar arithmetic
    FVector operator+(double Value) const
    {
        return FVector(X + Value, Y + Value, Z + Value);
    }

    FVector operator-(double Value) const
    {
        return FVector(X - Value, Y - Value, Z - Value);
    }

    // Compound assignment operators
    FVector& operator+=(const FVector& Other)
    {
        X += Other.X;
        Y += Other.Y;
        Z += Other.Z;
        return *this;
    }

    FVector& operator-=(const FVector& Other)
    {
        X -= Other.X;
        Y -= Other.Y;
        Z -= Other.Z;
        return *this;
    }

    FVector& operator*=(double Scale)
    {
        X *= Scale;
        Y *= Scale;
        Z *= Scale;
        return *this;
    }

    FVector& operator*=(const FVector& Other)
    {
        X *= Other.X;
        Y *= Other.Y;
        Z *= Other.Z;
        return *this;
    }

    FVector& operator/=(double Scale)
    {
        return *this *= 1.0 / Scale;
    }

    FVector& operator/=(const FVector& Other)
    {
        X /= Other.X;
        Y /= Other.Y;
        Z /= Other.Z;
        return *this;
    }

    // Length operations
    double Length() const
    {
        return std::sqrt(LengthSquared());
    }

    double LengthSquared() const
    {
        return X * X + Y * Y + Z * Z;
    }

    // Normalization
    FVector GetSafeNormal(double Tolerance = 1.e-8) const
    {
        const double SquaredLength = LengthSquared();
        if (SquaredLength == 1.0)
        {
            return *this;
        }
        if (SquaredLength < Tolerance * Tolerance)
        {
            return FVector::ZeroVector;
        }

        const double InvLength = 1.0 / std::sqrt(SquaredLength);
        return FVector(X * InvLength, Y * InvLength, Z * InvLength);
    }

    void Normalize(double Tolerance = 1.e-8)
    {
        const double SquaredLength = LengthSquared();
        if (SquaredLength < Tolerance * Tolerance)
        {
            *this = FVector::ZeroVector;
        }
        else
        {
            const double InvLength = 1.0 / std::sqrt(SquaredLength);
            *this *= InvLength;
        }
    }

    // Utility functions
    bool IsNearlyZero(double Tolerance = 1.e-8) const
    {
        return std::abs(X) < Tolerance
            && std::abs(Y) < Tolerance
            && std::abs(Z) < Tolerance;
    }

    bool IsZero() const
    {
        return X == 0.0 && Y == 0.0 && Z == 0.0;
    }

    bool IsUnit(double Tolerance = 1.e-4) const
    {
        return std::abs(1.0 - LengthSquared()) < Tolerance;
    }

    FVector GetAbs() const
    {
        return FVector(std::abs(X), std::abs(Y), std::abs(Z));
    }

    // Component-wise operations
    static FVector ComponentMin(const FVector& A, const FVector& B)
    {
        return FVector(
            std::fmin(A.X, B.X),
            std::fmin(A.Y, B.Y),
            std::fmin(A.Z, B.Z)
        );
    }

    static FVector ComponentMax(const FVector& A, const FVector& B)
    {
        return FVector(
            std::fmax(A.X, B.X),
            std::fmax(A.Y, B.Y),
            std::fmax(A.Z, B.Z)
        );
    }

    // Distance
    static double Distance(const FVector& A, const FVector& B);
    static double DistanceSquared(const FVector& A, const FVector& B);

    // Interpolation
    static FVector Lerp(const FVector& A, const FVector& B, double T);
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
    const double InvScale = 1.0 / Scale;
    return FVector(Vec.X * InvScale, Vec.Y * InvScale, Vec.Z * InvScale);
}

inline FVector operator/(const FVector& A, const FVector& B)
{
    return FVector(A.X / B.X, A.Y / B.Y, A.Z / B.Z);
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
