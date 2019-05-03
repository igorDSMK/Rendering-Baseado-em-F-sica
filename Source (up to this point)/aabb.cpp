#include "aabb.h"

AABB::AABB(const glm::dvec3 &min, const glm::dvec3 &max) :
             min_{min}, max_{max}, centroid_{0.5 * (min_ + max_)} 
{}

double AABB::getArea(void) const
{
    double x = (max_.x - min_.x);
    double y = (max_.y - min_.y);
    double z = (max_.z - min_.z);
    return 2.0 * (x * (y + z) + y * z);
}

bool AABB::intersect(const Ray &ray) const
{
    glm::vec3 invdir = (1.0f / ray.direction_);
    int sign[3];
    glm::vec3 bounds[2];

    sign[0] = (invdir.x < 0);
    sign[1] = (invdir.y < 0);
    sign[2] = (invdir.z < 0);
    bounds[0] = min_;
    bounds[1] = max_;

    float tmin = (bounds[sign[0]].x - ray.origin_.x) * invdir.x;
    float tmax = (bounds[1 - sign[0]].x - ray.origin_.x) * invdir.x;
    float tymin = (bounds[sign[1]].y - ray.origin_.y) * invdir.y;
    float tymax = (bounds[1 - sign[1]].y - ray.origin_.y) * invdir.y;

    if ((tmin > tymax) || (tymin > tmax)) return false;
    if (tymin > tmin) tmin = tymin;
    if (tymax < tmax) tmax = tymax;

    float tzmin = (bounds[sign[2]].z - ray.origin_.z) * invdir.z;
    float tzmax = (bounds[1 - sign[2]].z - ray.origin_.z) * invdir.z;

    if ((tmin > tzmax) || (tzmin > tmax)) return false;
    if (tzmin > tmin) tmin = tzmin;
    if (tzmax < tmax) tmax = tzmax;

    return true;
}