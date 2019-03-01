#include "triangle.h"

Triangle::Triangle(const glm::vec3 v1, const glm::vec3 v2,
 const glm::vec3 v3, const glm::vec3 color):
Primitive::Primitive{color}, v1{v1}, v2{v2}, v3{v3} {}

bool Triangle::intersect(const Ray &ray,
	IntersectionRecord &intersection_record) const
{
	float a, b, c, d, e, f, g, h, i, j, k, l,
		ak_minus_jb, bl_minus_kc, dh_minus_eg,
		ei_minus_hf, gf_minus_di, jc_minus_al,
		M, beta, gama, t;

	a = (v1.x - v2.x);
	b = (v1.y - v2.y);
	c = (v1.z - v2.z);
	d = (v1.x - v3.x);
	e = (v1.y - v3.y);
	f = (v1.z - v3.z);
	g = ray.direction_.x;
	h = ray.direction_.y;
	i = ray.direction_.z;
	j = (v1.x - ray.origin_.x);
	k = (v1.y - ray.origin_.y);
	l = (v1.z - ray.origin_.z);

	ak_minus_jb = a*k - j*b;
	bl_minus_kc = b*l - k*c;
	dh_minus_eg = d*h - e*g;
	ei_minus_hf = e*i - h*f;
	gf_minus_di = g*f - d*i;
	jc_minus_al = j*c - a*l;

	M = a*(ei_minus_hf)+b*(gf_minus_di)+c*(dh_minus_eg);

	t = -(f*(ak_minus_jb)+e*(jc_minus_al)+d*(bl_minus_kc)) / M;
	if (t < 0.0f) return false;

	gama = (i*(ak_minus_jb)+h*(jc_minus_al)+g*(bl_minus_kc)) / M;
	if (gama < 0.0f || gama > 1.0f) return false;

	beta = (j*(ei_minus_hf)+k*(gf_minus_di)+l*(dh_minus_eg)) / M;
	if (beta < 0.0f || beta >(1.0f - gama)) return false;

	intersection_record.t_ = t;
	intersection_record.position_ = ray.origin_ + intersection_record.t_ * ray.direction_;

	intersection_record.normal_ = glm::normalize(glm::cross(v2 - v1, v3 - v1));
	if (glm::dot(intersection_record.normal_, ray.direction_) > 0)
		intersection_record.normal_ = -intersection_record.normal_;

	intersection_record.color_ = color_;

	return true;
}

