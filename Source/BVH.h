#pragma once

#include "Hittable.h"
#include "HittableList.h"
#include "AABB.h"
#include "Math.h"

#include <algorithm>

class FBVHNode : public IHittable
{
public:
    FBVHNode(std::vector<std::shared_ptr<IHittable>>& Objects, size_t Start, size_t End)
    {
        BBox = FAABB::Empty;
        for (size_t i = Start; i < End; ++i)
        {
            BBox = FAABB(BBox, Objects[i]->BoundingBox());
        }

        int Axis = BBox.LongestAxis();

        auto Comparator = (Axis == 0) ? BoxCompareX : (Axis == 1) ? BoxCompareY : BoxCompareZ;

        size_t ObjectSpan = End - Start;

        if (ObjectSpan == 1)
        {
            Left = Objects[Start];
            Right = Objects[Start];
        }
        else if (ObjectSpan == 2)
        {
            Left = Objects[Start];
            Right = Objects[Start + 1];
        }
        else
        {
            std::sort(Objects.begin() + Start, Objects.begin() + End, Comparator);

            size_t Mid = Start + ObjectSpan / 2;
            Left = std::make_shared<FBVHNode>(Objects, Start, Mid);
            Right = std::make_shared<FBVHNode>(Objects, Mid, End);
        }

        BBox = FAABB(Left->BoundingBox(), Right->BoundingBox());
    }

    FBVHNode(FHittableList List)
        : FBVHNode(List.Objects, 0, List.Objects.size())
    {}

    virtual bool Hit(const FRay& Ray, const FInterval& Interval, FHitRecord& OutHitRecord) const override
    {
        if (!BBox.Hit(Ray, Interval))
        {
            return false;
        }

        bool bHitLeft = Left->Hit(Ray, Interval, OutHitRecord);
        bool bHitRight = Right->Hit(Ray, FInterval(Interval.Min, bHitLeft ? OutHitRecord.HitT : Interval.Max), OutHitRecord);

        return bHitLeft || bHitRight;
    }

    virtual FAABB BoundingBox() const override
    {
        return BBox;
    }

protected:
    std::shared_ptr<IHittable> Left;
    std::shared_ptr<IHittable> Right;
    FAABB BBox;

    static bool BoxCompare(const std::shared_ptr<IHittable>& A, const std::shared_ptr<IHittable>& B, int Axis)
    {
        if (Axis == 1)
        {
            return A->BoundingBox().Y.Min < B->BoundingBox().Y.Min;
        }
        if (Axis == 2)
        {
            return A->BoundingBox().Z.Min < B->BoundingBox().Z.Min;
        }
        return A->BoundingBox().X.Min < B->BoundingBox().X.Min;
    }

    static bool BoxCompareX(const std::shared_ptr<IHittable>& A, const std::shared_ptr<IHittable>& B)
    {
        return BoxCompare(A, B, 0);
    }

    static bool BoxCompareY(const std::shared_ptr<IHittable>& A, const std::shared_ptr<IHittable>& B)
    {
        return BoxCompare(A, B, 1);
    }

    static bool BoxCompareZ(const std::shared_ptr<IHittable>& A, const std::shared_ptr<IHittable>& B)
    {
        return BoxCompare(A, B, 2);
    }
};