
#define CATCH_CONFIG_MAIN
#include "catch2/catch.hpp"

#include "camera/camera.hpp"
#include "camera/film.hpp"
#include "shape/model.hpp"
#include "thread/thread_pool.hpp"
#include <glm/glm.hpp>

// inside only
#include "../inside.hpp"

TEST_CASE("Model:: simple dragon intersection rays", "[model]") {
    // 构造model路径
    fs::path models_path = Utility::path_models + "/simple_dragon.obj";
    std::cout << "[trace] model path    : " << models_path.string() << std::endl;
    REQUIRE(fs::exists(models_path));

    Film   film{192, 108};
    Camera camera{film, {-1, 0, 0}, {0, 0, 0}, 90};

    Model model{models_path};

    // Sphere sphere{{0, 0, 0}, 0.5f};

    Shape& shape = model;

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
    film.save(Utility::path_output / "test_simple_dragon.ppm");
    // REQUIRE(code == 0);
}
