#ifndef PRIMITIVE_H_
#define PRIMITIVE_H_

#include <memory>

#include "ray.h"
#include "intersection_record.h"

class Primitive
{
public:

    typedef std::unique_ptr< Primitive > PrimitiveUniquePtr;

    Primitive( void );

    Primitive (const glm::vec3 color, const glm::vec3 brdf, const glm::vec3 emittance, std::string type);

    virtual ~Primitive( void );

    virtual bool intersect( const Ray &ray,
                            IntersectionRecord &intersection_record ) const = 0;

     void setColor( glm::vec3 color );

     glm::vec3 color_;
     glm::vec3 brdf_;
     glm::vec3 emittance_;
     std::string type_;
};

#endif /* PRIMITIVE_H_ */

