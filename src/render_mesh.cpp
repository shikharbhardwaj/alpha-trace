// Render a .raw format file of a polygon mesh to an SVG
//
// Takes in camera parameters from the command line
//
#include <string>

#include <cxxopts.hpp>

#include <alpha/mesh_renderer.hpp>
#include <alpha/utils.hpp>

using namespace std;

void check_option(const cxxopts::ParseResult &result, std::string option) {
    if (result.count(option) == 0) {
        throw cxxopts::OptionException("Missing required option: " + option);
    }
}

int main(int argc, char **argv) {
    // Command line options configuration
    cxxopts::Options options("render_mesh", "Render a polygon mesh");

    options.add_options()("m,mesh_data", "Path to RAW mesh data file",
                          cxxopts::value<std::string>())
            ("o,output_file", "Path to output SVG",
             cxxopts::value<std::string>()->default_value("a.svg"))
            ("c,camera_config", "Path to Camera configuration",
             cxxopts::value<std::string>())
            ("v,verbose", "Enable verbose mode",
             cxxopts::value<bool>()->default_value("false"))
            ("z,cull_back_faces", "Enable back face culling",
             cxxopts::value<bool>()->default_value("false"))
            ("y,y_up", "Pass if the mesh-data is y-up (Blender style)",
             cxxopts::value<bool>()->default_value("false"))
            ("h,help", "Display help and exit");

    // Parse and set options
    try {
        auto result = options.parse(argc, argv);

        if (result.count("help") != 0) {
            // Display help and exit.
            std::cout << options.help() << std::endl;
            return 0;
        }

        // Check required options
        check_option(result, "mesh_data");
        check_option(result, "camera_config");

        // Configure options
        auto mesh_data_file = result["mesh_data"].as<std::string>();
        auto camera_config_file = result["camera_config"].as<std::string>();
        auto output_file = result["output_file"].as<std::string>();
        auto verbose = result["verbose"].as<bool>();
        auto cull_back_faces = result["cull_back_faces"].as<bool>();
        auto y_up = result["y_up"].as<bool>();

        spdlog::set_level(verbose ? spdlog::level::debug : spdlog::level::info);

        // Run the projection
        alpha::MeshRenderer(mesh_data_file, camera_config_file, output_file,
                            cull_back_faces, y_up).render();
    } catch (const cxxopts::OptionException &e) {
        alpha::exception_handler(e);
        std::cout << options.help() << std::endl;
    }
}
