#include <benchmark/benchmark.h>
#include <memory>

static void unique_ptr_create(benchmark::State& state) {
  for(auto _ : state) {
    std::unique_ptr<float> test;
    benchmark::DoNotOptimize(test);
  }
}

static void unique_ptr_get(benchmark::State& state) {
  std::unique_ptr<float> test(new float[32]);
  for(auto _ : state) {
    benchmark::DoNotOptimize(*test.get());
  }
}

static void unique_ptr_raw(benchmark::State& state) {
  std::unique_ptr<float> test(new float[32]);
  float* ptr = test.get();
  for(auto _ : state) {
    benchmark::DoNotOptimize(*ptr);
  }
}

BENCHMARK(unique_ptr_create);
BENCHMARK(unique_ptr_get);
BENCHMARK(unique_ptr_raw);

BENCHMARK_MAIN();
