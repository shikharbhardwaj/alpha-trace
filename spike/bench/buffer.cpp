#include <alpha/buffers.hpp>
#include <benchmark/benchmark.h>

static void Imagebuffer_create(benchmark::State& state) {
  for(auto _ : state) {
    int *ar = new int[100];
    benchmark::DoNotOptimize(ar[0]);
    delete[] ar;
  }
}

static void Imagebuffer_create2d(benchmark::State& state) {
  for(auto _ : state) {
    int **ar = new int*[10];
    for(int i = 0; i < 10; ++i) {
      ar[i] = new int[10];
    }
    benchmark::DoNotOptimize(ar[0]);
    for(int i = 0; i < 10; ++i) {
      delete[] ar[i];
    }
    delete[] ar;
  }
}

BENCHMARK(Imagebuffer_create);
BENCHMARK(Imagebuffer_create2d);

BENCHMARK_MAIN();
