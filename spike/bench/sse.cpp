#include <emmintrin.h>
#include <iostream>
#include <cstdio>
#include <cmath>
#include <chrono>
void normal(float *a, int N) {
    for (int i = 0; i < N; ++i)
        a[i] = sqrt(a[i]);
}

void sse(float *a, int N) {
    // We assume N % 4 == 0.
    int nb_iters = N / 4;
    __m128 *ptr = (__m128 *)a;

    for (int i = 0; i < nb_iters; ++i, ++ptr, a += 4)
        _mm_store_ps(a, _mm_sqrt_ps(*ptr));
}
using namespace std::chrono;
int main(int argc, char **argv) {
    if (argc != 2)
        return 1;
    int N = atoi(argv[1]);

    float *a;
    posix_memalign((void **)&a, 16, N * sizeof(float));

    for (int i = 0; i < N; ++i)
        a[i] = 3141592.65358;

    auto t1 = high_resolution_clock::now();
    { normal(a, N); }
    auto t2 = high_resolution_clock::now();
    std::cout << "Normal : " << duration_cast<milliseconds>(t2 - t1).count()
              << std::endl;
    for (int i = 0; i < N; ++i)
        a[i] = 3141592.65358;

    t1 = high_resolution_clock::now();
    { sse(a, N); }
    t2 = high_resolution_clock::now();
    std::cout << "SSE : " << duration_cast<milliseconds>(t2 - t1).count()
              << std::endl;
}
