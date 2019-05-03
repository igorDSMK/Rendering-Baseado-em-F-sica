#ifndef AABB_H_
#define AABB_H_

#include <iostream>
#include <iomanip>
#include <glm/glm.hpp>
#include "ray.h"
#include "intersection_record.h"

class AABB
{
  public:
    AABB(){};
    AABB(const glm::dvec3 &min, const glm::dvec3 &max);
    ~AABB(void){};

    double getArea(void) const;
    bool intersect(const Ray &ray) const;

    AABB operator+(const AABB &a) const
    {
        return AABB{glm::min(min_, a.min_), glm::max(max_, a.max_)};
    }

    glm::dvec3 min_;
    glm::dvec3 max_;
    glm::dvec3 centroid_;
};

#endif