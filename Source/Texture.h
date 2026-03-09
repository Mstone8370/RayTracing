#pragma once

#include "Vector.h"
#include "Color.h"
#include "Math.h"

class ITexture
{
public:
    virtual ~ITexture() = default;

    virtual FColor Value(double U, double V, const FVector& P) const = 0;
};


class FSolidColor : public ITexture
{
public:
    FSolidColor(const FColor& InAlbedo)
        : Albedo(InAlbedo)
    {}

    FSolidColor(double R, double G, double B)
        : Albedo(FColor(R, G, B))
    {}

    virtual FColor Value(double U, double V, const FVector& P) const override 
    {
        return Albedo;
    }

private:
    FColor Albedo;
};


class FCheckerTexture : public ITexture
{
public:
    FCheckerTexture(double Scale, const std::shared_ptr<ITexture>& InEven, const std::shared_ptr<ITexture>& InOdd)
        : InvScale(1.0 / Scale)
        , Even(InEven)
        , Odd(InOdd)
    {}

    FCheckerTexture(double Scale, const FColor& C1, const FColor& C2)
        : InvScale(1.0 / Scale)
        , Even(std::make_shared<FSolidColor>(C1))
        , Odd(std::make_shared<FSolidColor>(C2))
    {}

    virtual FColor Value(double U, double V, const FVector& P) const override
    {
        const int X = FMath::FloorToInt(P.X * InvScale);
        const int Y = FMath::FloorToInt(P.Y * InvScale);
        const int Z = FMath::FloorToInt(P.Z * InvScale);

        const bool bIsEven = ((X + Y + Z) & 1) == 0;

        return bIsEven ? Even->Value(U, V, P) : Odd->Value(U, V, P);
    }

private:
    double InvScale = 1.0;
    std::shared_ptr<ITexture> Even;
    std::shared_ptr<ITexture> Odd;
};
