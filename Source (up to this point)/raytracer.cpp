#include "raytracer.h"

RayTracer::RayTracer( Camera &camera,
                      const Scene &scene,
                      const glm::vec3 background_color,
                      Buffer &buffer, unsigned int maximum_depth ) :
     maximum_depth_(maximum_depth),
     camera_( camera ),
     scene_( scene ),
     background_color_{ background_color },
     buffer_( buffer )
{}

void RayTracer::integrate( void )
{
    IntersectionRecord intersection_record;
    int nSamples = 10;

    // Image space origin (i.e. x = 0 and y = 0) at the top left corner.

    // Loops over image rows
     #pragma omp parallel for schedule( dynamic, 1 ) //private (intersection_record)
    for ( std::size_t y = 0; y < buffer_.v_resolution_; y++ )
    {
        std::stringstream progress_stream;
        progress_stream << "\r  progress .........................: "
                        << std::fixed << std::setw( 6 )
                        << std::setprecision( 2 )
                        << 100.0 * y / ( buffer_.v_resolution_ - 1 )
                        << "%";

        std::clog << progress_stream.str();

        // Loops over image columns
        for ( std::size_t x = 0; x < buffer_.h_resolution_; x++ )
        {
             for (int sample = 0; sample < nSamples; sample++)
             {
                  intersection_record.t_ = std::numeric_limits< double >::max();

		        float w = Randomizer::getRandom();
		        float h = Randomizer::getRandom();

                  Ray ray{ camera_.getWorldSpaceRay( glm::vec2{ x + w, y + h } ) };

                  if ( scene_.intersect( ray, intersection_record ) )
                  {
                       buffer_.buffer_data_[x][y] += L(ray, 0);
                  }

             }

             buffer_.buffer_data_[x][y] /= nSamples;
        }
    }

     std::clog << std::endl;
     std::cout << "Num de threads: " << omp_get_max_threads() << std::endl;
}

glm::vec3 RayTracer::L(Ray ray, unsigned int curr_depth)
{
     glm::vec3 Lo = {0, 0, 0};
     IntersectionRecord intersection_record;
     intersection_record.t_ = std::numeric_limits< double >::max();

     if(curr_depth < this->maximum_depth_)
     {
          if ( scene_.intersect( ray, intersection_record ) )
          {
               if(intersection_record.material_.type_ == "diffuse")
               {
                    Ray refl_ray = intersection_record.get_new_ray();
                    float dot_ = glm::dot(refl_ray.direction_, intersection_record.normal_);

                    if (dot_ < 0)
                    {
                         refl_ray.direction_ = -refl_ray.direction_;
                         dot_ = -dot_;
                    }

                    Lo = intersection_record.material_.emittance_ + 2.0f * ((float)M_PI) * intersection_record.material_.brdf_ * L(refl_ray, ++curr_depth) * dot_;
               }
               else if(intersection_record.material_.type_ == "mirror")
               {
                    Ray refl_ray = intersection_record.get_reflection(ray);
                    Lo = L(refl_ray, ++curr_depth);
               }


          }
     }
     return Lo;

}
