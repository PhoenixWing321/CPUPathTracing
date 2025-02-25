
#define CATCH_CONFIG_MAIN
#include "catch2/catch.hpp"

#include "camera/camera.hpp"
#include "material/conductor_material.hpp"
#include "material/dielectric_material.hpp"
#include "material/diffuse_material.hpp"
#include "material/ground_material.hpp"
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
#include "../inside.hpp"

TEST_CASE("Lecture14:: test some models", "[Lecture14]") {
    // 构造model路径
    fs::path models_path = Utility::path_models + "/dragon_871k.obj";
    std::cout << "[trace] model path    : " << models_path.string() << std::endl;
    REQUIRE(fs::exists(models_path));

    Film   film{192 * 4, 108 * 4};
    Camera camera{film, {-10, 1.5, 0}, {0, 0, 0}, 45};

    Model  model(models_path);
    Sphere sphere{{0, 0, 0}, 1};
    Plane  plane{{0, 0, 0}, {0, 1, 0}};

    Scene scene{};
    for (int i = -3; i <= 3; i++) {
        scene.addShape(sphere, new DielectricMaterial{1.f + 0.2f * (i + 3), {1, 1, 1}},
                       {0, 0.5, i * 2}, {0.8, 0.8, 0.8});
    }
    for (int i = -3; i <= 3; i++) {
        glm::vec3 c = FilmRGB::GenerateHeatmapRGB((i + 3.f) / 6.f);
        scene.addShape(sphere,
                       new ConductorMaterial{
                           glm::vec3(2.f - c * 2.f),
                           glm::vec3(2.f + c * 3.f),
                       },
                       {0, 2.5, i * 2}, {0.8, 0.8, 0.8});
    }
    scene.addShape(model, new DielectricMaterial{1.8, FilmRGB(128, 191, 131)}, {-5, 0.4, 1.5},
                   {2, 2, 2});
    scene.addShape(model, new ConductorMaterial{{0.1, 1.2, 1.8}, {5, 2.5, 2}}, {-5, 0.4, -1.5},
                   {2, 2, 2});
    scene.addShape(plane, new GroundMaterial{FilmRGB(120, 204, 157)}, {0, -0.5, 0});
    auto* light_material = new DiffuseMaterial{{1, 1, 1}};
    light_material->setEmissive({0.95, 0.95, 1});
    scene.addShape(plane, light_material, {0, 10, 0});
    scene.build();

    NormalRenderer normal_renderer{camera, scene};
    normal_renderer.render(1, Utility ::path_models + "/Lecture14_normal.ppm");

    BoundsTestCountRenderer btc_renderer{camera, scene};
    btc_renderer.render(1, Utility ::path_models + "/Lecture14_BTC.ppm");
    TriangleTestCountRenderer ttc_renderer{camera, scene};
    ttc_renderer.render(1, Utility ::path_models + "/Lecture14_TTC.ppm");

    PathTracingRenderer path_tracing_renderer{camera, scene};
    path_tracing_renderer.render(128, Utility ::path_models + "/Lecture14_PT_cosine_test.ppm");
}

// Debug Mode
// load model 100ms
// parallelFor 700ms
// Film::save 130ms
// render 1spp normal.ppm 5504ms
// render 128spp test.ppm 1222161ms

// Release Mode
// load model 19ms
// parallelFor 400ms
// Film::save 53ms
// render 1spp normal.ppm 1189ms
// render 128spp test.ppm 91556ms

// Change parallelFor
// parallelFor 0ms

// Change Film::save
// Film::save 2ms

// Add Bounds
// load model 29ms
// render 1spp normal.ppm 156ms
// render 128spp test.ppm 30682ms

// Use rapidobj
// load model 2ms

// Add BVH
// render 1spp normal.ppm 146ms
// render 128spp test.ppm 5025ms

// Dragon 87k
// "origin" render 128spp test.ppm 3822ms
// "flatten" render 128spp test.ppm 3867ms
// "triangle index" render 128spp test.ppm 4009ms
// "32bit pack" render 128spp test.ppm 3928ms
// "inv_direction" render 128spp test.ppm 3752ms
// "SAH" render 128spp test.ppm 3865ms
// "871k dragon" render 128spp test.ppm 4032ms

// Without SAH
// Total Node Count: 142643
// Leaf Node Count: 71322
// Triangle Count: 87130
// Mean Leaf Node Triangle Count: 1.22164
// Max Leaf Node Triangle Count: 23
// Profile "Load model models/dragon_87k.obj": 2113ms

// With SAH
// Total Node Count: 164067
// Leaf Node Count: 82034
// Triangle Count: 87130
// Mean Leaf Node Triangle Count: 1.06212
// Max Leaf Node Triangle Count: 8
// Profile "Load model models/dragon_87k.obj": 16023ms

// With 3Dim SAH
// Total Node Count: 174195
// Leaf Node Count: 87098
// Triangle Count: 87130
// Mean Leaf Node Triangle Count: 1.00037
// Max Leaf Node Triangle Count: 3
// Profile "Load model models/dragon_87k.obj": 51655ms

// 871k Dragon BVH
// Total Node Count: 1742423
// Leaf Node Count: 871212
// Triangle Count: 871306
// Mean Leaf Node Triangle Count: 1.00011
// Max Leaf Node Triangle Count: 3
// Profile "Load model models/dragon_871k.obj": 519741ms

// 871k Dragon BVH 12 Buckets
// Total Node Count: 1742425
// Leaf Node Count: 871213
// Triangle Count: 871306
// Mean Leaf Node Triangle Count: 1.00011
// Max Leaf Node Triangle Count: 3
// Profile "Load model models/dragon_871k.obj": 26482ms

// 871k Dragon BVH Change ThreadPool
// Profile "Load model models/dragon_871k.obj": 14564ms

// 871k Dragon BVH Add Allocator
// Profile "Load model models/dragon_871k.obj": 8328ms

// 871k Dragon BVH Vector Reserve
// Profile "Load model models/dragon_871k.obj": 6140ms

// render 100 shape instances scene
// Profile "Render 128spp test.ppm": 18613ms

// render 100 shape instances scene with SceneBVH
// Profile "Render 128spp test.ppm": 7628ms
