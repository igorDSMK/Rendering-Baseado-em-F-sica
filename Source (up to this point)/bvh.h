#ifndef BVH_H
#define BVH_H

#include <iostream>
#include <deque>
#include <queue>
#include <algorithm>
#include "primitive.h"
#include "aabb.h"

/* BVH tem duas estruturas: Nó (BVHNode), e Area aabb da primitiva (PrimitiveAABBArea) */
class BVH
{
  public:
    struct BVHNode
    {
        ~BVHNode(void)
        {
            if (left_)
            {
                delete left_;
                left_ = nullptr;
            }

            if (right_)
            {
                delete right_;
                right_ = nullptr;
            }
        }

        std::size_t first_;
        std::size_t last_;
        AABB aabb_;
        BVHNode *left_ = nullptr;
        BVHNode *right_ = nullptr;
    };

    struct PrimitiveAABBArea
    {
        std::size_t primitive_id_;
        glm::dvec3 centroid_;
        AABB aabb_;
        double left_area_;
        double right_area_;

        AABB left_aabb_;
        AABB right_aabb_;
    };

    BVH(const std::vector<Primitive::PrimitiveUniquePtr> &primitives);

    ~BVH(void);

    bool intersect(const Ray &ray, IntersectionRecord &intersection_record) const;

  private:
    struct Comparator
    {
        static bool sortInX(const PrimitiveAABBArea &lhs, const PrimitiveAABBArea &rhs)
        {
            return lhs.centroid_.x < rhs.centroid_.x;
        }

        static bool sortInY(const PrimitiveAABBArea &lhs, const PrimitiveAABBArea &rhs)
        {
            return lhs.centroid_.y < rhs.centroid_.y;
        }

        static bool sortInZ(const PrimitiveAABBArea &lhs, const PrimitiveAABBArea &rhs)
        {
            return lhs.centroid_.z < rhs.centroid_.z;
        }
    };

    double SAH(std::size_t s1_size, double s1_area, std::size_t s2_size, double s2_area, double s_area);
    void splitNode(BVHNode **node, std::deque<PrimitiveAABBArea> &s, std::size_t first, std::size_t last, 
                    double s_area);
    bool traverse(const BVHNode *node, const Ray &ray, IntersectionRecord &intersection_record) const;

    int size(BVHNode * node);
    BVHNode *root_node_ = nullptr;

    double cost_intersec_tri_ = 0.8;
    double cost_intersec_aabb_ = 0.2;

    std::deque<long unsigned int> primitive_id_;

    const std::vector<Primitive::PrimitiveUniquePtr> &primitives_;

    std::size_t primitives_inserted_ = 0;
};

#endif