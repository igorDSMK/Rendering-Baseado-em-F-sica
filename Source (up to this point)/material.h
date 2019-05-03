#ifndef MATERIAL_H
#define MATERIAL_H

#include <glm/glm.hpp>
#include <iostream>

class Material
{
public:
    Material(void);
    Material(const glm::vec3 brdf, const glm::vec3 emittance, std::string type);

    glm::vec3 brdf_;
    glm::vec3 emittance_;
    std::string type_;

};


#endif