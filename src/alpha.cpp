// Alpha-trace : Main app
#include <algorithm>
#include <cstring>
#include <iostream>
#include <alpha/math.hpp>
#include <alpha/rasteriser.hpp>

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
            std::cout << "\nNot implemented yet :D";
        }
    }
}
