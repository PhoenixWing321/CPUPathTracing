
#define CATCH_CONFIG_MAIN
#include "catch2/catch.hpp"

#include "camera/film.hpp"
#include "thread/thread_pool.hpp"

// inside only
#include "inside.hpp"

class TestTask : public Task {
public:
    TestTask(std::atomic<int>& counter)
        : _counter(counter) {}

    void run() override {
        _counter++;
        // 模拟一些工作
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }

private:
    std::atomic<int>& _counter;
};

TEST_CASE("ThreadPool基本功能测试", "[ThreadPool]") {
    // if (1) return;
    SECTION("创建线程池") {
        ThreadPool pool(4);
        REQUIRE_NOTHROW(ThreadPool(4));
    }

    SECTION("添加和执行任务") {
        ThreadPool       pool(2);
        std::atomic<int> counter(0);
        const int        taskCount = 10;

        // 创建并添加任务
        for (int i = 0; i < taskCount; ++i) {
            pool.addTask(new TestTask(counter));
        }

        // 等待一段时间确保任务完成
        std::this_thread::sleep_for(std::chrono::milliseconds(200));

        REQUIRE(counter == taskCount);
    }

    SECTION("线程池自动选择线程数") {
        ThreadPool       pool(0); // 应该使用硬件支持的线程数
        std::atomic<int> counter(0);
        const int        taskCount = 5;

        for (int i = 0; i < taskCount; ++i) {
            pool.addTask(new TestTask(counter));
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        REQUIRE(counter == taskCount);
    }
}

TEST_CASE("ThreadPool压力测试", "[ThreadPool][stress]") {
    if (1) return;

    ThreadPool       pool(4);
    std::atomic<int> counter(0);
    const int        taskCount = 10;

    // 添加大量任务
    for (int i = 0; i < taskCount; ++i) {
        pool.addTask(new TestTask(counter));
    }

    // 等待所有任务完成
    std::this_thread::sleep_for(std::chrono::seconds(2));
    REQUIRE(counter == taskCount);
}

TEST_CASE("ThreadPool::Parallel测试", "[ThreadPool]") {
    // 创建一个小尺寸的测试影像
    const size_t width  = 1920;
    const size_t height = 1080;
    Film         film(width, height);

    // 添加测试保存时间的代码
    auto start = std::chrono::high_resolution_clock::now();
    thread_pool.parallelFor(1000, 800, [ & ](size_t x, size_t y) {
        film.addSample(x, y, {x / 1920.f, y / 1920.f, 0.2});
    });

    thread_pool.wait();
    auto end      = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "并行耗时: " << duration.count() << " ms" << std::endl;

    film.save(Utility::path_models + "/test_ThradPool_parallelFor.ppm");
    auto end2 = std::chrono::high_resolution_clock::now();
    duration  = std::chrono::duration_cast<std::chrono::milliseconds>(end2 - end);
    std::cout << "保存耗时: " << duration.count() << " ms" << std::endl;

    // REQUIRE(code == 0);

    // cout << " test parallel(), code = " << code << endl;
}