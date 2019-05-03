#include "material.h"

Material::Material( void )
{ }

Material::Material(const glm::vec3 brdf, const glm::vec3 emittance, std::string type):
        brdf_{ brdf/(float) M_PI},
        emittance_{ emittance },
        type_(type)
{ }