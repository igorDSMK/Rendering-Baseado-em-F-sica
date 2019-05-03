#ifndef INTERSECTION_RECORD_H_
#define INTERSECTION_RECORD_H_

#include <glm/glm.hpp>
#include "randomizer.h"
#include <cmath>
#include "onb.h"
#include "ray.h"
#include "material.h"

struct IntersectionRecord
{
    float t_;
    glm::vec3 position_;
    glm::vec3 normal_;
    Material material_;

    Ray get_new_ray() // diffuse
    {
        glm::vec3 direction;
        ONB onb;
        Ray new_ray;

        float r1 = Randomizer::getRandom();
        float r2 = Randomizer::getRandom();

        float theta = glm::acos(1 - r1);
        float phi = 2.0f * ((float)M_PI) * r2;

        direction.x = sin(theta) * cos(phi);
        direction.y = sin(theta) * sin(phi);
        direction.z = cos(theta);

        onb.setFromV(this->normal_);

        new_ray.origin_ = this->position_ + (this->normal_ * 0.001f);
        new_ray.direction_ = onb.getBasisMatrix() * direction;

        return new_ray;
    }

    Ray get_reflection(Ray &ray) // mirror
    {
        ONB onb_;
        Ray newray;

        onb_.setFromV(this->normal_);
        glm::vec3 newdirection = glm::transpose(onb_.getBasisMatrix()) * ray.direction_;
        newdirection = {newdirection.x, -newdirection.y, newdirection.z};
        newray = {this->position_ + (this->normal_ * 0.001f), onb_.getBasisMatrix() * newdirection};

        return newray;
    }
};

#endif /* INTERSECTION_RECORD_H_ */

