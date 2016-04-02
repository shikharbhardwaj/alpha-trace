#include <fstream>
#include <cstdlib>
#include <cstdio>

int main() {
    std::ifstream ifs;
    ifs.open("./tex.pbm");
    std::string header;
    uint32_t w, h, l;
    ifs >> header;
    ifs >> w >> h >> l;
    ifs.ignore();
    unsigned char *pixels = new unsigned char[w * h * 3];
    ifs.read((char *)pixels, w * h * 3);
    // sample
    int nsamples = 8;
    srand48(13);
    float avgr = 0, avgg = 0, avgb = 0;
    float sumr = 0, sumg = 0, sumb = 0;
    for (int n = 0; n < nsamples; ++n) {
        float x = drand48() * w;
        float y = drand48() * h;
        int i = ((int)(y)*w + (int)(x)) * 3;
        sumr += pixels[i];
        sumg += pixels[i + 1];
        sumb += pixels[i + 2];
    }
    sumr /= nsamples;
    sumg /= nsamples;
    sumb /= nsamples;
    for (uint32_t y = 0; y < h; ++y) {
        for (uint32_t x = 0; x < w; ++x) {
            int i = (y * w + x) * 3;
            avgr += pixels[i];
            avgg += pixels[i + 1];
            avgb += pixels[i + 2];
        }
    }
    avgr /= w * h;
    avgg /= w * h;
    avgb /= w * h;
    printf("Average %0.2f %0.2f %0.2f, Approximation %0.2f %0.2f %0.2f\n", avgr,
           avgg, avgb, sumr, sumg, sumb);
    delete[] pixels;
    return 0;
}
