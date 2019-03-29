#include "triangle2.h"
#define EPSILON 0.000001f

Triangle2::Triangle2( const glm::vec3 v1, const glm::vec3 v2,const glm::vec3 v3,
     const glm::vec3 color, const glm::vec3 brdf, const glm::vec3 emittance, std::string type):

     Primitive::Primitive{color, brdf, emittance, type}, v1{v1}, v2{v2}, v3{v3}
{}

bool Triangle2::intersect(const Ray &ray,
	IntersectionRecord &intersection_record) const
{
	glm::vec3 edge1, edge2, tvec, pvec, qvec;
	float det, inv_det, t, u, v;

	edge1 = v2 - v1;
	edge2 = v3 - v1;
	pvec = glm::cross(ray.direction_, edge2);
	det = glm::dot(edge1, pvec);

	if (det > -EPSILON && det < EPSILON) return false;

	inv_det = 1.0f / det;
	tvec = ray.origin_ - v1;

	u = glm::dot(tvec, pvec)*inv_det;
	if (u < 0.0f || u > 1.0f) return false;

	qvec = glm::cross(tvec, edge1);

	v = glm::dot(ray.direction_, qvec)*inv_det;
	if (v < 0.0f || (u + v) > 1.0f) return false;

	t = glm::dot(edge2, qvec)*inv_det;

	intersection_record.t_ = t;
	intersection_record.position_ = ray.origin_ + intersection_record.t_ * ray.direction_;

	intersection_record.normal_ = glm::normalize(glm::cross(v2 - v1, v3 - v1));
	if (glm::dot(intersection_record.normal_, ray.direction_) > 0.0f)
		intersection_record.normal_ = -intersection_record.normal_;

	intersection_record.color_ = color_;
     intersection_record.brdf_ = brdf_ / ((float) M_PI);
     intersection_record.emittance_ = emittance_;
     intersection_record.type_ = type_;

	return true;
}
