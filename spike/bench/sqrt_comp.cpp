#define NONIUS_RUNNER
#include <nonius/nonius.h++>
#include <cmath>
#include <random>
float InvSqrt(float x) {
    float xhalf = 0.5f * x;
    int i = *(int *)&x;             // get bits for floating value
    i = 0x5f375a86 - (i >> 1);      // gives initial guess y0
    x = *(float *)&i;               // convert bits back to float
    x = x * (1.5f - xhalf * x * x); // Newton step, repeating increases accuracy
    return x;
}
NONIUS_BENCHMARK("Quake", [](nonius::chronometer meter) {
    meter.measure([] { return InvSqrt(19937); });
});
NONIUS_BENCHMARK("std", [](nonius::chronometer meter) {
    meter.measure([] { return 1.0 / sqrt(19937); });
});
