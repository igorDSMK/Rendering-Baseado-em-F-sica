#include "randomizer.h"

namespace Randomizer
{
    float seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::uniform_real_distribution<float> distribuition(0.0f, 1.0f);
    std::mt19937 generator(seed);
    
    float getRandom()
    {
        float r = distribuition(generator);    
        while (r == 1.0f) r = distribuition(generator);
        return r;
    }

}