
#define CATCH_CONFIG_MAIN
#include "catch2/catch.hpp"

#include "material/diffuse_material.hpp"
#include "material/specular_material.hpp"
#include "renderer/debug_renderer.hpp"
#include "renderer/normal_renderer.hpp"
#include "renderer/path_tracing_renderer.hpp"
#include "shape/model.hpp"
#include "shape/plane.hpp"
#include "shape/scene.hpp"
#include "shape/sphere.hpp"
#include "util/rgb.hpp"

// inside only
#include "inside.hpp"

TEST_CASE("Lecture13:: test some models", "[Lecture13]") {
    // 构造model路径
    fs::path models_path = Utility::path_models + "/dragon_871k.obj";
    std::cout << "[trace] model path    : " << models_path.string() << std::endl;
    REQUIRE(fs::exists(models_path));

    Film   film{192 * 4, 108 * 4};
    Camera camera{film, {-12, 5, -12}, {0, 0, 0}, 45};

    Model  model(models_path);
    Sphere sphere{{0, 0, 0}, 1};
    Plane  plane{{0, 0, 0}, {0, 1, 0}};

    Scene scene{};
    RNG   rng{1234};
    for (int i = 0; i < 10000; i++) {
        glm::vec3 random_pos{
            rng.uniform() * 100 - 50,
            rng.uniform() * 2,
            rng.uniform() * 100 - 50,
        };
        float u = rng.uniform();
        if (u < 0.9) {
            Material* material;
            if (rng.uniform() > 0.5) {
                material = new SpecularMaterial{RGB(202, 159, 117)};
            }
            else {
                material = new DiffuseMaterial{RGB(202, 159, 117)};
            }
            scene.addShape(model, material, random_pos, {1, 1, 1},
                           {rng.uniform() * 360, rng.uniform() * 360, rng.uniform() * 360});
        }
        else if (u < 0.95) {
            scene.addShape(sphere,
                           new SpecularMaterial{{rng.uniform(), rng.uniform(), rng.uniform()}},
                           random_pos, {0.4, 0.4, 0.4});
        }
        else {
            random_pos.y += 6;
            auto* material = new DiffuseMaterial{{0, 0, 0}};
            material->setEmissive({rng.uniform() * 4, rng.uniform() * 4, rng.uniform() * 4});
            scene.addShape(sphere, material, random_pos);
        }
    }
    scene.addShape(plane, new DiffuseMaterial{RGB(120, 204, 157)}, {0, -0.5, 0});
    scene.build();

    NormalRenderer normal_renderer{camera, scene};
    normal_renderer.render(1, Utility::path_models + "/Lecture13_normal.ppm");

    BoundsTestCountRenderer btc_renderer{camera, scene};
    btc_renderer.render(1, Utility::path_models + "/Lecture13_BTC.ppm");
    TriangleTestCountRenderer ttc_renderer{camera, scene};
    ttc_renderer.render(1, Utility::path_models + "/Lecture13_TTC.ppm");

    PathTracingRenderer path_tracing_renderer{camera, scene};
    path_tracing_renderer.render(128, Utility::path_models + "/Lecture13_PT_cosine_test.ppm");
}
