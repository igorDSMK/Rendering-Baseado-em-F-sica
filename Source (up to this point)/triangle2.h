#ifndef TRIANGLE2_H_
#define TRIANGLE2_H_

#include <glm/glm.hpp>
#include <glm/geometric.hpp>
#include "primitive.h"
#include "intersection_record.h"
#include "ray.h"

class Triangle2 : public Primitive
{
public:

	Triangle2(void) = delete;
	Triangle2(const glm::vec3 v1, const glm::vec3 v2,const glm::vec3 v3, Material material);

	bool intersect(const Ray &ray, IntersectionRecord &intersection_record) const;
	AABB getAABB(void) const;

	glm::vec3 v1, v2, v3;
};

#endif //TRIANGLE2_H_
