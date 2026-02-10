#pragma once

#include "Hittable.h"

#include <memory>
#include <vector>

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

    bool Hit(const FRay& Ray, double TMin, double TMax, FHitRecord& OutHitRecord) const override
    {
        FHitRecord TempRecord;
        bool bHit = false;
        double ClosestHitT = TMax;

        for (const std::shared_ptr<IHittable>& Object : Objects)
        {
            if (Object->Hit(Ray, TMin, ClosestHitT, TempRecord))
            {
                bHit = true;
                // if (TempRecord.HitT < ClosestHitT)
                // {
                //     ClosestHitT = TempRecord.HitT;
                //     OutHitRecord = TempRecord;
                // }
                ClosestHitT = TempRecord.HitT;
                OutHitRecord = TempRecord;
            }
        }

        return bHit;
    }
};