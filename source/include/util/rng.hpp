#pragma once

#include <random>

class RNG {
public:
    using result_type = unsigned int;
    RNG(result_type seed) { setSeed(seed); }
    RNG() : RNG(0) {}

    void setSeed(result_type seed) { gen.seed(seed); }
    float uniform() const { return uniform_distribution(gen); } // [0, 1)
private:
    mutable std::mt19937 gen;
    mutable std::uniform_real_distribution<float> uniform_distribution { 0, 1 };
};
