#ifndef INTERSECTION_RECORD_H_
#define INTERSECTION_RECORD_H_
#define _USE_MATH_DEFINES

#include <glm/glm.hpp>
#include <random>
#include <chrono>
#include <math.h>
#include "onb.h"

struct IntersectionRecord
{
    float t_;
    glm::vec3 position_;
    glm::vec3 normal_;
    glm::vec3 color_;
    glm::vec3 brdf_;
    glm::vec3 emittance_;
    std::string type_;

    Ray get_new_ray() // diffuse
    {
        glm::vec3 direction;
        ONB onb;
        Ray new_ray;

        auto seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::uniform_real_distribution<float> distribuition(0.0f, 1.0f);
        std::mt19937 generator(seed);

        float r1 = distribuition(generator);
        float r2 = distribuition(generator);
        while (r1 == 1.0f)
            r1 = distribuition(generator);
        while (r2 == 1.0f)
            r2 = distribuition(generator);

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

