#include <alpha/buffers_fast.hpp>
#pragma comment(lib, "Shlwapi.lib")
#include <benchmark/benchmark.h>

static void Imagebuffer_create(benchmark::State& state) {
	for (auto _ : state) {
		alpha::buffers::Imagebuffer buffer(1920, 1080);
		benchmark::DoNotOptimize(buffer);
	}
}

static void Imagebuffer_fill(benchmark::State& state) {
	for (auto _ : state) {
		alpha::buffers::Imagebuffer buffer(256, 256);
		const int maxcolor = 255;
		for (int x = 0; x < 256; ++x) {
			for (int y = 0; y < 256; ++y) {
				uint8_t r = (x + y) % maxcolor;
				uint8_t g = (2 * x + y) % maxcolor;
				uint8_t b = (x + 2 * y) % maxcolor;
				buffer.set(x, y, r, g, b);
			}
		}
		benchmark::DoNotOptimize(buffer);
	}
}

BENCHMARK(Imagebuffer_create);
BENCHMARK(Imagebuffer_fill);

BENCHMARK_MAIN();
