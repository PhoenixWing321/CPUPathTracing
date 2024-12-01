
#define CATCH_CONFIG_MAIN
#include "catch2/catch.hpp"

#include "camera/camera.hpp"
#include "camera/film.hpp"
#include "material/specular_material.hpp"
#include "shape/model.hpp"
#include "shape/plane.hpp"
#include "shape/scene.hpp"
#include "shape/sphere.hpp"
#include "thread/thread_pool.hpp"
#include "util/rgb.hpp"

// inside only
#include "inside.hpp"

TEST_CASE("Scene:: Scene intersection rays", "[scene]") {
    // 构造model路径
    fs::path models_path = Utility::path_models + "/simple_dragon.obj";
    std::cout << "[trace] model path    : " << models_path.string() << std::endl;
    REQUIRE(fs::exists(models_path));

    std::atomic<int> count = 0;

    Film   film{192, 108};
    Camera camera{film, {-0.6, 0., 0}, {0, 0, 0}, 90};

    Sphere sphere{{0, 0, 0}, 0.5f};
    Plane  plane{{0, 0, 0}, {0, 1, 0}};
    Model  model{models_path};

    Scene scene{};

    // Material* material = new SpecularMaterial{RGB(202, 159, 117)};
    // scene.addShape(model, material);
    // scene.addShape(sphere, material, {0, 0, 1}, {0.3, 0.3, 0.3});
    // scene.addShape(plane, material);

    // glm::vec3 light_pos{-1, 2, 1};

    // thread_pool.parallelFor(film.getWidth(), film.getHeight(), [ & ](size_t x, size_t y) {
    //     auto ray    = camera.generateRay({x, y});
    //     auto result = scene.intersect(ray, 1e-5, 10000.f);
    //     if (result.has_value()) {
    //         auto  L      = glm::normalize(light_pos - result->hit_point);
    //         float cosine = glm::max(0.f, glm::dot(result->normal, L));

    //         film.addSample(x, y, {cosine, cosine, cosine});
    //     }

    //     int n = ++count;
    //     if (n % film.getWidth() == 0) {
    //         cout << static_cast<float>(n) / (film.getHeight() * film.getWidth()) << endl;
    //     }
    // });

    // thread_pool.wait();
    // film.save(Utility::path_models + "/test_Scene.ppm");
    // REQUIRE(code == 0);
}
