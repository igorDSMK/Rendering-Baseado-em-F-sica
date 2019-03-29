#include "primitive.h"

Primitive::Primitive( void )
{}

Primitive::Primitive (const glm::vec3 color, const glm::vec3 brdf, const glm::vec3 emittance, std::string type):
         color_{color}, brdf_{brdf}, emittance_{emittance}, type_(type)
{}

Primitive::~Primitive( void )
{}

void Primitive::setColor( glm::vec3 color )
{
     color_ = color;
}

