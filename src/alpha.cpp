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
int main(int argc, char **argv) {
    std::vector<std::string> args(argc);
    for (int i = 0; i < argc; i++) {
        args[i] = std::string(argv[i]);
    }
    // Now process the args
    if (std::find(args.begin(), args.end(), "-h") != args.end()) {
        help();
    } else if (std::find(args.begin(), args.end(), "-r") != args.end()) {
        if (std::find(args.begin(), args.end(), "-d") + 2 >= args.end()) {
            std::cerr
                << "\nNo image dimensions specified. Use -h flag for help";
        } else {
            auto pos = std::find(args.begin(), args.end(), "-d");
            int width = atoi((pos + 1)->c_str());
            int height = atoi((pos + 2)->c_str());
            std::cout << "\nRasterising image with dimensions : " << width
                      << " x " << height << std::endl;
            alpha::Rasteriser rast(width, height);
            alpha::Vec2i orig = {0, 0};
            alpha::Vec2i final = {width, height};
            alpha::Vec2i finalx = {width, 0};
            rast.draw_triangle(orig, finalx, final);
            rast.dump_as_ppm("heha.ppm");
        }
    }
}
