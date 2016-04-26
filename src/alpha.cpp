// Alpha-trace : Main app
#include <iostream>
#include <algorithm>
#include <cstring>
#include <math_alpha.hpp>
#include <rasteriser_alpha.hpp>
void help() {
    std::cout << "\t\tAlpha-trace command line utility";
    std::cout << "\nSwitches : ";
    std::cout << "\n -h \t\t:\t Display help";
    std::cout << "\n -d WIDTH HEIGHT:\t Set output image dimensions";
    std::cout << "\n -r \t\t:\t Use rasterisation for image generation";
    std::cout << std::endl;
}
int find_pos(char **begin, char **end, const char *val) {
    int sz = end - begin;
    for (int i = 0; i < sz; i++) {
        if (strcmp(*(begin + i), val) == 0) {
            return i;
        }
    }
    return sz;
}
bool is_there(char **begin, char **end, const char *val) {
    while (begin != end) {
        if (strcmp(*begin, val) == 0) {
            return true;
        }
        begin++;
    }
    return false;
}
int main(int argc, char **argv) {
    if (argc == 1) {
        // Display help
        help();
    }
    if (argc > 1) {
        if (is_there(argv, argv + argc, "-h")) {
            help();
        } else if (is_there(argv, argv + argc, "-r")) {
            int pos = find_pos(argv, argv + argc, "-d");
            if (pos == argc) {
                std::cout
                    << "Specify image dimensions with flag -d WIDTH HEIGHT"
                    << std::endl;
            } else {
                int height, width, a, b, c, d, e, f;
                width = atoi(*(argv + pos + 1));
                height = atoi(*(argv + pos + 2));
                std::cout << "Rasterising image with dimensions : " << width
                          << "x" << height << std::endl;
                std::cout
                    << "Enter co-ordinates of triangle vertexes to render, EOF "
                    << "starts rendering" << std::endl;
                std::vector<alpha::Vec2i> triangles;
                while (std::cin >> a >> b >> c >> d >> e >> f) {
                    triangles.push_back({a, b});
                    triangles.push_back({c, d});
                    triangles.push_back({e, f});
                }
                std::cout << "Starting rendering...";
                alpha::Rasteriser rast(width, height);
                for (auto it = triangles.begin(); it + 2 < triangles.end();
                     it += 3) {
                    rast.draw_triangle(*(it), *(it + 1), *(it + 2));
                }
                std::cout << "Done";
                std::cout << "\nDumping framebuffer to disk";
                rast.dump_as_ppm("result.ppm");
            }
        }
    }
}
