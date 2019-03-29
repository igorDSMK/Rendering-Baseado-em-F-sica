#include "scene.h"

Scene::Scene( void )
{}

Scene::~Scene( void )
{}

bool Scene::intersect( const Ray &ray,
                       IntersectionRecord &intersection_record ) const
{
    bool intersection_result = false;
    IntersectionRecord tmp_intersection_record;
    std::size_t num_primitives = primitives_.size();

    // Loops over the list of primitives, testing the intersection of each primitive against the given ray
    for ( std::size_t primitive_id = 0; primitive_id < num_primitives; primitive_id++ )
        if ( primitives_[primitive_id]->intersect( ray, tmp_intersection_record ) )
            if ( ( tmp_intersection_record.t_ < intersection_record.t_ ) && ( tmp_intersection_record.t_ > 0.0 ) )
            {
                intersection_record = tmp_intersection_record;
                intersection_result = true; // the ray intersects a primitive!
            }

    return intersection_result;
}

void Scene::load( void )
{
     /*Assimp::Importer importer;


     const aiScene *scene = importer.ReadFile("obj/monkey.obj",
                                             aiProcess_CalcTangentSpace |
                                                 aiProcess_Triangulate |
                                                 aiProcess_JoinIdenticalVertices |
                                                 aiProcess_SortByPType);
    for (unsigned int j = 0; j < scene->mNumMeshes; j++)
    {
        auto mesh = scene->mMeshes[j];

        for (unsigned int i = 0; i < mesh->mNumFaces; i++)
        {
            auto face = mesh->mFaces[i];

            auto v1 = mesh->mVertices[face.mIndices[0]];
            auto v2 = mesh->mVertices[face.mIndices[1]];
            auto v3 = mesh->mVertices[face.mIndices[2]];
            primitives_.push_back(Primitive::PrimitiveUniquePtr(new Triangle2(glm::vec3{v1.x, -v1.y, v1.z},
                                                                             glm::vec3{v2.x, -v2.y, v2.z},
                                                                             glm::vec3{v3.x, -v3.y, v3.z},
                                                                             glm::vec3{0.0f, 1.0f, 0.0f}, // cor
                                                                             glm::vec3{0.725f, 0.0f, 0.933f},  // brdf
                                                                             glm::vec3{0.0f, 0.0f, 0.0f}, "diffuse" ) )); // emittance
        }
    }


      scene = importer.ReadFile("obj/espelho.obj",
                                              aiProcess_CalcTangentSpace |
                                                  aiProcess_Triangulate |
                                                  aiProcess_JoinIdenticalVertices |
                                                  aiProcess_SortByPType);
     for (unsigned int j = 0; j < scene->mNumMeshes; j++)
     {
         auto mesh = scene->mMeshes[j];

         for (unsigned int i = 0; i < mesh->mNumFaces; i++)
         {
             auto face = mesh->mFaces[i];

             auto v1 = mesh->mVertices[face.mIndices[0]];
             auto v2 = mesh->mVertices[face.mIndices[1]];
             auto v3 = mesh->mVertices[face.mIndices[2]];
             primitives_.push_back(Primitive::PrimitiveUniquePtr(new Triangle2(glm::vec3{v1.x, v1.y, v1.z},
                                                                              glm::vec3{v2.x, v2.y, v2.z},
                                                                              glm::vec3{v3.x, v3.y, v3.z},
                                                                              glm::vec3{0.0f, 1.0f, 0.0f},
                                                                             glm::vec3{0.8f, 0.8f, 0.8f},
                                                                             glm::vec3{0.0, 0.0, 0.0}, "mirror" ) )); // emittance
         }
     }

     scene = importer.ReadFile("obj/lampada1.obj",
                                             aiProcess_CalcTangentSpace |
                                                 aiProcess_Triangulate |
                                                 aiProcess_JoinIdenticalVertices |
                                                 aiProcess_SortByPType);
    for (unsigned int j = 0; j < scene->mNumMeshes; j++)
    {
        auto mesh = scene->mMeshes[j];

        for (unsigned int i = 0; i < mesh->mNumFaces; i++)
        {
            auto face = mesh->mFaces[i];

            auto v1 = mesh->mVertices[face.mIndices[0]];
            auto v2 = mesh->mVertices[face.mIndices[1]];
            auto v3 = mesh->mVertices[face.mIndices[2]];
            primitives_.push_back(Primitive::PrimitiveUniquePtr(new Triangle2(glm::vec3{v1.x, v1.y, v1.z},
                                                                             glm::vec3{v2.x, v2.y, v2.z},
                                                                             glm::vec3{v3.x, v3.y, v3.z},
                                                                             glm::vec3{0.0f, 1.0f, 0.0f}, // cor
                                                                             glm::vec3{0.0f, 0.0f, 0.0f},  // brdf
                                                                             glm::vec3{4.8f, 4.8f, 4.8f}, "diffuse" ) )); // emittance
        }
    }


    scene = importer.ReadFile("obj/lampada2.obj",
                                            aiProcess_CalcTangentSpace |
                                                aiProcess_Triangulate |
                                                aiProcess_JoinIdenticalVertices |
                                                aiProcess_SortByPType);
   for (unsigned int j = 0; j < scene->mNumMeshes; j++)
   {
       auto mesh = scene->mMeshes[j];

       for (unsigned int i = 0; i < mesh->mNumFaces; i++)
       {
           auto face = mesh->mFaces[i];

           auto v1 = mesh->mVertices[face.mIndices[0]];
           auto v2 = mesh->mVertices[face.mIndices[1]];
           auto v3 = mesh->mVertices[face.mIndices[2]];
           primitives_.push_back(Primitive::PrimitiveUniquePtr(new Triangle2(glm::vec3{v1.x, v1.y, v1.z},
                                                                            glm::vec3{v2.x, v2.y, v2.z},
                                                                            glm::vec3{v3.x, v3.y, v3.z},
                                                                            glm::vec3{0.0f, 1.0f, 0.0f}, // cor
                                                                            glm::vec3{0.0f, 0.0f, 0.0f},  // brdf
                                                                            glm::vec3{4.8f, 4.8f, 4.8f}, "diffuse" ) )); // emittance
       }
   }

   primitives_.push_back(Primitive::PrimitiveUniquePtr(new Sphere(glm::vec3{0.0f, 0.0f, 0.0f},
                                                                    glm::vec3{0.0f, 0.0f, 0.0f}, // cor
                                                                    glm::vec3{0.0f, 0.0f, 0.0f},  // brdf
                                                                    glm::vec3{10.0f, 10.0f, 10.0f}, "diffuse", 1.0f ) )); // emittance
*/
	primitives_.push_back(Primitive::PrimitiveUniquePtr(new Sphere(glm::vec3{ 0.0f, -3.0f, 0.0f }, // sombra: -0.7f, -0.5f, 0.0f / padrao: 0.0f, -3.0f, 0.0f
																	glm::vec3{ 0.0f, 0.0f, 0.0f }, // cor
																	glm::vec3{ 1.0f, 1.0f, 1.0f },  // brdf
																	glm::vec3{ 50.0f, 50.0f, 50.0f }, "diffuse", 0.3f))); // emittance

	primitives_.push_back(Primitive::PrimitiveUniquePtr(new Sphere(glm::vec3{ 0.0f, 0.6f, 0.0f },
																	glm::vec3{ 0.0f, 0.0f, 0.0f }, // cor
																	glm::vec3{ 0.0f, 0.0f, 1.0f },  // brdf
																	glm::vec3{ 0.0f, 0.0f, 0.0f }, "diffuse", 0.4f))); // emittance

	primitives_.push_back(Primitive::PrimitiveUniquePtr(new Triangle2(glm::vec3{ -2.0f, 1.0f, 2.0f },
																	glm::vec3{ -2.0f, 1.0f, -4.0f },
																	glm::vec3{ 2.0f, 1.0f, -4.0f },
																	glm::vec3{ 0.0f, 1.0f, 0.0f }, // cor
																	glm::vec3{ 0.75f, 0.75f, 0.75f },  // brdf
																	glm::vec3{ 0.0f, 0.0f, 0.0f }, "diffuse"))); // emittance

	primitives_.push_back(Primitive::PrimitiveUniquePtr(new Triangle2(glm::vec3{ -2.0f, 1.0f, 2.0f },
																	glm::vec3{ 2.0f, 1.0f, -4.0f },
																	glm::vec3{ 2.0f, 1.0f, 2.0f },
																	glm::vec3{ 0.0f, 1.0f, 0.0f }, // cor
																	glm::vec3{ 0.75f, 0.75f, 0.75f },  // brdf
																	glm::vec3{ 0.0f, 0.0f, 0.0f }, "diffuse"))); // emittance

	primitives_.push_back(Primitive::PrimitiveUniquePtr(new Triangle2(glm::vec3{ -2.0f, -3.0f, 2.0f },
																	glm::vec3{ -2.0f, -3.0f, -4.0f },
																	glm::vec3{ 2.0f, -3.0f, -4.0f },
																	glm::vec3{ 0.0f, -3.0f, 0.0f }, // cor
																	glm::vec3{ 0.75f, 0.75f, 0.75f },  // brdf
																	glm::vec3{ 0.0f, 0.0f, 0.0f }, "diffuse"))); // emittance

	primitives_.push_back(Primitive::PrimitiveUniquePtr(new Triangle2(glm::vec3{ -2.0f, -3.0f, 2.0f },
																	glm::vec3{ 2.0f, -3.0f, -4.0f },
																	glm::vec3{ 2.0f, -3.0f, 2.0f },
																	glm::vec3{ 0.0f, -3.0f, 0.0f }, // cor
																	glm::vec3{ 0.75f, 0.75f, 0.75f },  // brdf
																	glm::vec3{ 0.0f, 0.0f, 0.0f }, "diffuse"))); // emittance

	primitives_.push_back(Primitive::PrimitiveUniquePtr(new Triangle2(glm::vec3{ -2.0f, 1.0f, 2.0f },
																	glm::vec3{ 2.0f, 1.0f, 2.0f },
																	glm::vec3{ -2.0f, -4.0f, 2.0f },
																	glm::vec3{ 0.0f, 1.0f, 0.0f }, // cor
																	glm::vec3{ 0.75f, 0.75f, 0.75f },  // brdf
																	glm::vec3{ 0.0f, 0.0f, 0.0f }, "diffuse"))); // emittance

	primitives_.push_back(Primitive::PrimitiveUniquePtr(new Triangle2(glm::vec3{ 2.0f, 1.0f, 2.0f },
																	glm::vec3{ 2.0f, -4.0f, 2.0f },
																	glm::vec3{ -2.0f, -4.0f, 2.0f },
																	glm::vec3{ 0.0f, 1.0f, 0.0f }, // cor
																	glm::vec3{ 0.75f, 0.75f, 0.75f },  // brdf
																	glm::vec3{ 0.0f, 0.0f, 0.0f }, "diffuse"))); // emittance

	primitives_.push_back(Primitive::PrimitiveUniquePtr(new Triangle2(glm::vec3{ 2.0f, 1.0f, 2.0f },
																	glm::vec3{ 2.0f, 1.0f, -4.0f },
																	glm::vec3{ 2.0f, -4.0f, 2.0f },
																	glm::vec3{ 0.0f, 1.0f, 0.0f }, // cor
																	glm::vec3{ 0.75f, 0.75f, 0.75f },  // brdf
																	glm::vec3{ 0.0f, 0.0f, 0.0f }, "diffuse"))); // emittance

	primitives_.push_back(Primitive::PrimitiveUniquePtr(new Triangle2(glm::vec3{ 2.0f, 1.0f, -4.0f },
																	glm::vec3{ 2.0f, -4.0f, -4.0f },
																	glm::vec3{ 2.0f, -4.0f, 2.0f },
																	glm::vec3{ 0.0f, 1.0f, 0.0f }, // cor
																	glm::vec3{ 0.75f, 0.75f, 0.75f },  // brdf
																	glm::vec3{ 0.0f, 0.0f, 0.0f }, "diffuse"))); // emittance

	primitives_.push_back(Primitive::PrimitiveUniquePtr(new Triangle2(glm::vec3{ -2.0f, 1.0f, 2.0f },
																	glm::vec3{ -2.0f, 1.0f, -4.0f },
																	glm::vec3{ -2.0f, -4.0f, 2.0f },
																	glm::vec3{ 0.0f, 1.0f, 0.0f }, // cor
																	glm::vec3{ 0.75f, 0.75f, 0.75f },  // brdf
																	glm::vec3{ 0.0f, 0.0f, 0.0f }, "diffuse"))); // emittance

	primitives_.push_back(Primitive::PrimitiveUniquePtr(new Triangle2(glm::vec3{ -2.0f, 1.0f, -4.0f },
																	glm::vec3{ -2.0f, -4.0f, -4.0f },
																	glm::vec3{ -2.0f, -4.0f, 2.0f },
																	glm::vec3{ 0.0f, 1.0f, 0.0f }, // cor
																	glm::vec3{ 0.75f, 0.75f, 0.75f },  // brdf
																	glm::vec3{ 0.0f, 0.0f, 0.0f }, "diffuse"))); // emittance

	/*primitives_.push_back(Primitive::PrimitiveUniquePtr(new Triangle2(glm::vec3{ -2.0f, 1.0f, -4.0f },
																	glm::vec3{ 2.0f, 1.0f, -4.0f },
																	glm::vec3{ -2.0f, -4.0f, -4.0f },
																	glm::vec3{ 0.0f, 1.0f, 0.0f }, // cor
																	glm::vec3{ 0.75f, 0.75f, 0.75f },  // brdf
																	glm::vec3{ 0.0f, 0.0f, 0.0f }, "diffuse"))); // emittance

	primitives_.push_back(Primitive::PrimitiveUniquePtr(new Triangle2(glm::vec3{ 2.0f, 1.0f, -4.0f },
																	glm::vec3{ 2.0f, -4.0f, -4.0f },
																	glm::vec3{ -2.0f, -4.0f, -4.0f },
																	glm::vec3{ 0.0f, 1.0f, 0.0f }, // cor
																	glm::vec3{ 0.75f, 0.75f, 0.75f },  // brdf
																	glm::vec3{ 0.0f, 0.0f, 0.0f }, "diffuse"))); // emittance*/
}

