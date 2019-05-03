#ifndef RAYTRACER_H_
#define RAYTRACER_H_

#include <sstream>
#include <iomanip>
#include <cmath>
#include <omp.h>

#include "camera.h"
#include "scene.h"
#include "buffer.h"
#include "randomizer.h"

class RayTracer
{
public:

     RayTracer( Camera &camera,
               const Scene &scene, const glm::vec3 background_color,
               Buffer &buffer, unsigned int maximum_depth );

    void integrate( void );
    glm::vec3 L(Ray ray, unsigned int curr_depth);
    unsigned int maximum_depth_;

private:

    const Camera &camera_;

    const Scene &scene_;

    glm::dvec3 background_color_;

    Buffer &buffer_;

};

#endif /* RAYTRACER_H_ */

