#pragma once

#include "Interval.h"
#include "Ray.h"
#include "Math.h"

class FAABB
{
public:
    FInterval X;
    FInterval Y;
    FInterval Z;

    FAABB()
        : X()
        , Y()
        , Z()
    {}

    FAABB(const FInterval& InX, const FInterval& InY, const FInterval& InZ)
        : X(InX)
        , Y(InY)
        , Z(InZ)
    {}

    FAABB(const FVector& A, const FVector& B)
        : X(FMath::Min(A.X, B.X), FMath::Max(A.X, B.X))
        , Y(FMath::Min(A.Y, B.Y), FMath::Max(A.Y, B.Y))
        , Z(FMath::Min(A.Z, B.Z), FMath::Max(A.Z, B.Z))
    {}

    FAABB(const FAABB& Box1, const FAABB& Box2)
        : X(FInterval(Box1.X, Box2.X))
        , Y(FInterval(Box1.Y, Box2.Y))
        , Z(FInterval(Box1.Z, Box2.Z))
    {}

    const FInterval& AxisInterval(int Axis) const
    {
        if (Axis == 1)
        {
            return Y;
        }
        if (Axis == 2)
        {
            return Z;
        }
        return X;
    }

    bool Hit(const FRay& Ray, FInterval RayT) const
    {
        const FVector& RayOrigin = Ray.Origin;
        const FVector& RayDirection = Ray.Direction;

        for (int Axis = 0; Axis < 3; ++Axis)
        {
            const FInterval& Interval = AxisInterval(Axis);
            const double InvDirection = 1.0 / RayDirection[Axis];

            double T0 = (Interval.Min - RayOrigin[Axis]) * InvDirection;
            double T1 = (Interval.Max - RayOrigin[Axis]) * InvDirection;

            if (T0 < T1)
            {
                if (T0 > RayT.Min)
                {
                    RayT.Min = T0;
                }
                if (T1 < RayT.Max)
                {
                    RayT.Max = T1;
                }
            }
            else
            {
                if (T1 > RayT.Min)
                {
                    RayT.Min = T1;
                }
                if (T0 < RayT.Max)
                {
                    RayT.Max = T0;
                }
            }

            if (RayT.Max <= RayT.Min)
            {
                return false;
            }
        }

        return true;
    }

    int LongestAxis() const
    {
        if (X.Size() > Y.Size())
        {
            return (X.Size() > Z.Size()) ? 0 : 2;
        }
        else
        {
            return (Y.Size() > Z.Size()) ? 1 : 2;
        }
    }

    static const FAABB Empty;
    static const FAABB Universe;
};