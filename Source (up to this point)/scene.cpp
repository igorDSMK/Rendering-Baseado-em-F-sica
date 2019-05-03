#include "scene.h"

Scene::Scene( void )
{}

Scene::~Scene( void )
{
    if ( bvh_ )
    {
        delete bvh_;
        bvh_ = nullptr;
    }
}



bool Scene::intersect(const Ray &ray,
                      IntersectionRecord &intersection_record) const
{
    bool intersection_result = false;
    intersection_result = bvh_->intersect(ray, intersection_record);
    return intersection_result;
}

void Scene::buildBVH(void)
{
    bvh_ = new BVH(primitives_);
}

void Scene::load( void )
{
     Assimp::Importer importer;


     const aiScene *scene = importer.ReadFile("models/monkey.obj",
                                             aiProcess_CalcTangentSpace |
                                                 aiProcess_Triangulate |
                                                 aiProcess_JoinIdenticalVertices |
                                                 aiProcess_SortByPType);

    Material monkey(glm::vec3{0.725f, 0.0f, 0.933f}, glm::vec3{0.0f, 0.0f, 0.0f}, "diffuse"); // brdf, emittance, type
    for (unsigned int j = 0; j < scene->mNumMeshes; j++)
    {
        auto mesh = scene->mMeshes[j];

        for (unsigned int i = 0; i < mesh->mNumFaces; i++)
        {
            auto face = mesh->mFaces[i];

            auto v1 = mesh->mVertices[face.mIndices[0]];
            auto v2 = mesh->mVertices[face.mIndices[1]];
            auto v3 = mesh->mVertices[face.mIndices[2]];
            primitives_.push_back(Primitive::PrimitiveUniquePtr(new Triangle2(glm::vec3{-v1.x, -v1.y, -v1.z}, glm::vec3{-v2.x, -v2.y, -v2.z},
                                                                             glm::vec3{-v3.x, -v3.y, -v3.z}, monkey) ));
        }
    }
    

    Material luz(glm::vec3{1.0f, 1.0f, 1.0f}, glm::vec3{50.0f, 50.0f, 50.0f}, "diffuse"); // brdf, emittance, type
    Sphere *s1 = new Sphere(glm::vec3{0.0f, -3.0f, 0.0f}, 0.3f, luz);
    primitives_.push_back(Primitive::PrimitiveUniquePtr(s1));

    // Material m2(glm::vec3{0.0f, 0.0f, 1.0f}, glm::vec3{0.0f, 0.0f, 0.0f}, "diffuse");
    // Sphere *s2 = new Sphere(glm::vec3{0.0f, 0.6f, 0.0f}, 0.4f, m2); // emittance
    // primitives_.push_back(Primitive::PrimitiveUniquePtr(s2));
    
    Material m3(glm::vec3{0.75f, 0.75f, 0.75f}, glm::vec3{0.0f, 0.0f, 0.0f}, "diffuse");
    Triangle2 *t1 = new Triangle2(glm::vec3{-2.0f, 1.0f, 2.0f}, glm::vec3{-2.0f, 1.0f, -4.0f}, glm::vec3{2.0f, 1.0f, -4.0f}, m3);
    Triangle2 *t2 = new Triangle2(glm::vec3{-2.0f, 1.0f, 2.0f}, glm::vec3{2.0f, 1.0f, -4.0f}, glm::vec3{2.0f, 1.0f, 2.0f}, m3);
    Triangle2 *t3 = new Triangle2(glm::vec3{-2.0f, -3.0f, 2.0f}, glm::vec3{-2.0f, -3.0f, -4.0f}, glm::vec3{2.0f, -3.0f, -4.0f}, m3);
    Triangle2 *t4 = new Triangle2(glm::vec3{-2.0f, -3.0f, 2.0f}, glm::vec3{2.0f, -3.0f, -4.0f}, glm::vec3{2.0f, -3.0f, 2.0f}, m3);
    Triangle2 *t5 = new Triangle2(glm::vec3{-2.0f, 1.0f, 2.0f}, glm::vec3{2.0f, 1.0f, 2.0f}, glm::vec3{-2.0f, -4.0f, 2.0f}, m3);
    Triangle2 *t6 = new Triangle2(glm::vec3{2.0f, 1.0f, 2.0f}, glm::vec3{2.0f, -4.0f, 2.0f}, glm::vec3{-2.0f, -4.0f, 2.0f}, m3);
    Triangle2 *t7 = new Triangle2(glm::vec3{2.0f, 1.0f, 2.0f}, glm::vec3{2.0f, 1.0f, -4.0f}, glm::vec3{2.0f, -4.0f, 2.0f}, m3);
    Triangle2 *t8 = new Triangle2(glm::vec3{2.0f, 1.0f, -4.0f}, glm::vec3{2.0f, -4.0f, -4.0f}, glm::vec3{2.0f, -4.0f, 2.0f}, m3);
    Triangle2 *t9 = new Triangle2(glm::vec3{-2.0f, 1.0f, 2.0f}, glm::vec3{-2.0f, 1.0f, -4.0f}, glm::vec3{-2.0f, -4.0f, 2.0f}, m3);
    Triangle2 *t10 = new Triangle2(glm::vec3{-2.0f, 1.0f, -4.0f}, glm::vec3{-2.0f, -4.0f, -4.0f}, glm::vec3{-2.0f, -4.0f, 2.0f}, m3);
    primitives_.push_back(Primitive::PrimitiveUniquePtr(t1));
    primitives_.push_back(Primitive::PrimitiveUniquePtr(t2));
    primitives_.push_back(Primitive::PrimitiveUniquePtr(t3));
    primitives_.push_back(Primitive::PrimitiveUniquePtr(t4));
    primitives_.push_back(Primitive::PrimitiveUniquePtr(t5));
    primitives_.push_back(Primitive::PrimitiveUniquePtr(t6));
    primitives_.push_back(Primitive::PrimitiveUniquePtr(t7));
    primitives_.push_back(Primitive::PrimitiveUniquePtr(t8));
    primitives_.push_back(Primitive::PrimitiveUniquePtr(t9));
    primitives_.push_back(Primitive::PrimitiveUniquePtr(t10));
}

