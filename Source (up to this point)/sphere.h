#ifndef SPHERE_H_
#define SPHERE_H_

#include <glm/glm.hpp>
#include "primitive.h"
#include "intersection_record.h"
#include "ray.h"

class Sphere : public Primitive
{
public:

    Sphere( void );

    Sphere(const glm::vec3 center, const glm::vec3 color, const glm::vec3 brdf,
         const glm::vec3 emittance, std::string type, float radius);

    bool intersect( const Ray &ray,
                    IntersectionRecord &intersection_record ) const;

     glm::vec3 center_;
     float radius_;

private:

    static const float kIntersectionTestEpsilon_;
};

#endif /* SPHERE_H_ */

