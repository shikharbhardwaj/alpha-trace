#include <iostream>
#include <random>

#include <benchmark/benchmark.h>

#include <alpha/math.hpp>
#include <vectorclass/vectorclass.h>

// A simple microbenchmark for finding the throughput differences between
// the math libraries.

using namespace std;

std::random_device rd;
std::mt19937_64 gen(rd());

static void xmm_create(benchmark::State& state) {
  std::uniform_real_distribution<float> dist;
  float mult = dist(gen);

  for(auto _ : state) {
    Vec4f test;
    benchmark::DoNotOptimize(test * mult);
    benchmark::DoNotOptimize(test * mult);
    benchmark::DoNotOptimize(test * mult);
  }
}

static void crude_create(benchmark::State& state) {
  std::uniform_real_distribution<float> dist;
  float mult = dist(gen);

  for(auto _ : state) {
    alpha::math::Vec3f test;
    benchmark::DoNotOptimize(test * mult);
    benchmark::DoNotOptimize(test * mult);
    benchmark::DoNotOptimize(test * mult);
  }
}

BENCHMARK(xmm_create);
BENCHMARK(crude_create);

BENCHMARK_MAIN();
