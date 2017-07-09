#include <benchmark/benchmark.h>
#include <math_alpha.hpp>
#include <gmtl/gmtl.h>
#include <armadillo>

static void gmtl_vector_create(benchmark::State& state) {
  while (state.KeepRunning()){
    gmtl::Vec3f some_vec = {1, 4, 5};
    benchmark::DoNotOptimize(some_vec);
  }
}

static void gmtl_vector_dot(benchmark::State& state) {
  while (state.KeepRunning()){
    gmtl::Vec3f some_vec1 = {1, 4, 5}, some_vec2 = {5, 3, 5};
    benchmark::DoNotOptimize(gmtl::dot(some_vec1, some_vec2));
  }
}
static void alpha_vector_create(benchmark::State& state) {
  while (state.KeepRunning()){
    alpha::math::Vec3f some_vec({1, 4, 5});
    benchmark::DoNotOptimize(some_vec);
  }
}

static void alpha_vector_dot(benchmark::State& state) {
  while (state.KeepRunning()){
    alpha::math::Vec3f some_vec1 = {1, 4, 5}, some_vec2 = {5, 3, 5};
    float val = some_vec1.dot_product(some_vec2);
    benchmark::DoNotOptimize(val);
  }
}

static void arma_vector_create(benchmark::State& state) {
  while (state.KeepRunning()){
    arma::vec3 some_vec({1, 4, 5});
    benchmark::DoNotOptimize(some_vec);
  }
}

static void arma_vector_dot(benchmark::State& state) {
  while (state.KeepRunning()){
    arma::vec3 some_vec1 = {1, 4, 5}, some_vec2 = {5, 3, 5};
    float val = arma::dot(some_vec1, some_vec2);
    benchmark::DoNotOptimize(val);
  }
}
static void float_muliply(benchmark::State& state) {
  while (state.KeepRunning()){
    float val1 = 0.4, val2 = 0.5;
    benchmark::DoNotOptimize(val1 * val2);
  }
}
// Is math_alpha fast enough?
// Register the function as a benchmark
BENCHMARK(gmtl_vector_create);
BENCHMARK(gmtl_vector_dot);
BENCHMARK(alpha_vector_create);
BENCHMARK(alpha_vector_dot);
BENCHMARK(arma_vector_create);
BENCHMARK(arma_vector_dot);
BENCHMARK(float_muliply);
BENCHMARK_MAIN();
