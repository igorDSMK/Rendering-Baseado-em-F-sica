#include "brdf.h"

BRDF::BRDF(const glm::vec3 brdf) :
	brdf_{ brdf } {}


Ray get_new_ray_difuse(IntersectionRecord &intersection_record) {

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

	onb.setFromV(intersection_record.normal_);

	new_ray.origin_ = intersection_record.position_ + (intersection_record.normal_ * 0.001f);
	new_ray.direction_ = onb.getBasisMatrix() * direction;

	return new_ray;
}
