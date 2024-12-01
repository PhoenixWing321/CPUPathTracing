
#define CATCH_CONFIG_MAIN
#include "catch2/catch.hpp"

#include "camera/camera.hpp"
#include "camera/film.hpp"
#include "shape/plane.hpp"
#include "thread/thread_pool.hpp"
#include <glm/glm.hpp>

// inside only
#include "../inside.hpp"

TEST_CASE("Plane:: Plane intersection rays", "[Plane]") {

    Film   film{192, 108};
    Camera camera{film, {-0.6, 0.1, 0}, {0, 0, 0}, 90};

    Plane plane{{0, 0, 0}, {0, 1, 0}};

    // Sphere sphere{{0, 0, 0}, 0.5f};

    Shape& shape = plane;

    glm::vec3 light_pos{-1, 2, 1};

    thread_pool.parallelFor(film.getWidth(), film.getHeight(), [ & ](size_t x, size_t y) {
        auto ray    = camera.generateRay({x, y});
        auto result = shape.intersect(ray, 1e-5f, 10000.f);
        if (result.has_value()) {
            auto  L      = glm::normalize(light_pos - result->hit_point);
            float cosine = glm::max(0.f, glm::dot(result->normal, L));

            film.addSample(x, y, {cosine, cosine, cosine});
        }
    });

    thread_pool.wait();
    auto path = Utility::path_output / "test_Plane.ppm";
    std::cout<<"save to "<< path<<std::endl;
    film.save(path);
    // REQUIRE(code == 0);
}
