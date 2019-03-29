#ifndef BRDF_H_
#define BRDF_H_
#define _USE_MATH_DEFINES

#include <glm/glm.hpp>
#include <random>
#include <chrono>
#include <math.h>
#include "onb.h"
#include "intersection_record.h"
#include "ray.h"

class BRDF {

	BRDF::BRDF(const glm::vec3 brdf);

	glm::vec3 brdf_;

	Ray get_new_ray_difuse(IntersectionRecord &intersection_record);
};

#endif //BRDF_H_