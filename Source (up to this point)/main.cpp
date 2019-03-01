#include <ctime>
#include <iostream>
#include "main.h"

using namespace std;

int main( void )
{
    unsigned int x_resolution = 512;
    unsigned int y_resolution = 512;
	int l;


    /*OrthographicCamera camera{ -1.25f,
                                1.25f,
                               -1.25f,
                                1.25f,
                                glm::ivec2{ x_resolution, y_resolution },
                                glm::vec3{ 0.0f, 0.0f,  1.0f },     // position
                                glm::vec3{ 0.0f, 1.0f,  0.0f },     // up
                                glm::vec3{ 0.0f, 0.0f, -1.0f } };   // look at


     */
	PinholeCamera camera{ -2.5f,
		2.5f,
		-2.5f,
		2.5f,
		6.0f,
		glm::ivec2{ x_resolution, y_resolution },
		glm::vec3{ 2.5, 0.0f, 3.0f },     // position 3.48113, 3.58115f, 4.06472f
		glm::vec3{ 0.0f, 1.0f,  0.0f },     // up
		glm::vec3{ 0.0f, 0.0f, -1.0f } };   // look at

    Scene scene{};

	clock_t begin = clock();

    scene.load();

    Buffer rendering_buffer{ x_resolution, y_resolution };
    glm::vec3 background_color{ 0.0f, 0.0f, 0.0f };

    // Set up the renderer.
    RayTracer rt( camera,
                  scene,
                  background_color,
                  rendering_buffer );

    rt.integrate(); // Renders the final image.

    // Save the rendered image to a .ppm file.
    rendering_buffer.save( "output_image.ppm" );

	clock_t end = clock();
	double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
	cout << elapsed_secs << " segs\n";
	cin >> l;

    return EXIT_SUCCESS;
}

