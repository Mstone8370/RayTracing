#pragma once

#include "Hittable.h"

#include <memory>
#include <vector>

#include "Interval.h"

class FHittableList : public IHittable
{
public:
    std::vector<std::shared_ptr<IHittable>> Objects;

    FHittableList() = default;
    FHittableList(std::shared_ptr<IHittable> Object)
    {
        Add(Object);
    }
    
    void Add(std::shared_ptr<IHittable> Object)
    {
        Objects.push_back(Object);
    }

    void Clear()
    {
        Objects.clear();
    }

    bool Hit(const FRay& Ray, const FInterval& Interval, FHitRecord& OutHitRecord) const override
    {
        FHitRecord TempRecord;
        bool bHit = false;
        double ClosestHitT = Interval.Max;

        for (const std::shared_ptr<IHittable>& Object : Objects)
        {
            if (Object->Hit(Ray, FInterval(Interval.Min, ClosestHitT), TempRecord))
            {
                bHit = true;
                ClosestHitT = TempRecord.HitT;
                OutHitRecord = TempRecord;
            }
        }

        return bHit;
    }
};