
#define CATCH_CONFIG_MAIN
#include "catch2/catch.hpp"

#include "camera/camera.hpp"
#include "camera/film.hpp"
#include "camera/ray.hpp"
#include "shape/sphere.hpp"
#include "thread/thread_pool.hpp"
#include <glm/glm.hpp>

// inside only
#include "inside.hpp"

float t_min = 1e-5f;
float t_max = 1e10f;
TEST_CASE("Sphere intersection tests", "[sphere]") {
    SECTION("Ray hits sphere") {
        Sphere sphere{glm::vec3(0.0f, 0.0f, 0.0f), 1.0f}; // 原点球，半径1

        // 从z轴正方向射向球心
        Ray ray{
            glm::vec3(0.0f, 0.0f, 2.0f), // origin
            glm::vec3(0.0f, 0.0f, -1.0f) // direction (normalized)
        };

        auto hit = sphere.intersect(ray, t_min, t_max);
        REQUIRE(hit.has_value());
        REQUIRE(hit->t == Approx(1.0f)); // 相交点在z=1处
    }

    SECTION("Ray misses sphere") {
        Sphere sphere{glm::vec3(0.0f, 0.0f, 0.0f), 1.0f};

        // 从远处平行y轴射出，应该错过球体
        Ray ray{
            glm::vec3(2.0f, 0.0f, 0.0f), // origin
            glm::vec3(0.0f, 1.0f, 0.0f)  // direction
        };

        auto hit = sphere.intersect(ray, t_min, t_max);
        REQUIRE_FALSE(hit.has_value());
    }

    SECTION("Ray starts inside sphere") {
        // Sphere sphere{glm::vec3(0.0f, 0.0f, 0.0f), 2.0f};

        // // 从球内部向外射出
        // Ray ray{
        //     glm::vec3(0.0f, 0.0f, 0.0f), // origin
        //     glm::vec3(0.0f, 0.0f, 1.0f)  // direction
        // };

        // TODO 内部应该可以相交

        // auto hit = sphere.intersect(ray, t_min, t_max);
        // REQUIRE(hit.has_value());
        // REQUIRE(*hit == Approx(2.0f)); // 相交点在z=2处
    }

    SECTION("Ray starts on sphere surface") {
        Sphere sphere{glm::vec3(0.0f, 0.0f, 0.0f), 1.0f};

        // 从球面向外射出
        Ray ray{
            glm::vec3(1.0f, 0.0f, 0.0f), // origin (on sphere surface)
            glm::vec3(1.0f, 0.0f, 0.0f)  // direction
        };

        auto hit = sphere.intersect(ray, t_min, t_max);
        CHECK_FALSE(hit.has_value()); // 不应该检测到相交
    }
}

TEST_CASE("Sphere:: intersection rays", "[sphere]") {

    Film   film{192, 108};
    Camera camera{film, {0, 0, 1}, {0, 0, 0}, 90};

    Sphere    sphere{{0, 0, 0}, 0.5f};
    glm::vec3 light_pos{1, 1, 1};

    thread_pool.parallelFor(film.getWidth(), film.getHeight(), [ & ](size_t x, size_t y) {
        auto ray    = camera.generateRay({x, y});
        auto result = sphere.intersect(ray, t_min, t_max);
        if (result.has_value()) {
            auto  L      = glm::normalize(light_pos - result->hit_point);
            float cosine = glm::max(0.f, glm::dot(result->normal, L));

            film.addSample(x, y, {cosine, cosine, cosine});
        }
    });

    thread_pool.wait();
    film.save(Utility::path_models + "/test_sphere.ppm");
    // REQUIRE(code == 0);
}
