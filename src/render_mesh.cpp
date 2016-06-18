// Render a .raw format file of a polygon mesh to an SVG
//
// Takes in camera parameters from the command line
//
#include <camera_alpha.hpp>
#include <rasteriser_alpha.hpp>
#include <svg_alpha.hpp>
#include <vector>
#include <vertex_import.hpp>
bool verbose = false;
bool blender = false;
void help() {
    // The command line parameters
    std::cout << "render_mesh : Render a polygon mesh" << std::endl;
    std::cout << "-o file_name\t: Name of the exported SVG" << std::endl;
    std::cout << "-c file_name\t: Name of the camera config file" << std::endl;
    std::cout << "-m file_name\t: Name of the RAW mesh data file" << std::endl;
    std::cout << "-v          \t: Be verbose" << std::endl;
    std::cout << "-b          \t: Pass if the vertex data is Y-up\n";
    std::cout << "-t          \t: Pass if the camera is column major\n";
    std::cout << "-z          \t: Pass to hide non-visible faces\n";
    std::cout << "-h          \t: Display help and exit" << std::endl;
    std::exit(0);
}
void print_info(const std::string &msg) {
    if (verbose) {
        std::cout << "INFO : " << msg << std::endl;
    }
}
std::string get_name(const std::string &switch_val,
                     const std::vector<std::string> &args) {
    // Get file name from the switch
    auto it = std::find(args.begin(), args.end(), switch_val);
    if (it + 1 == args.end()) {
        std::cerr << switch_val << " requires a file name" << std::endl;
        std::exit(1);
    }
    return *(it + 1);
}
int main(int argc, char **argv) {
    std::vector<std::string> args(argc);
    for (int i = 0; i < argc; i++) {
        args[i] = std::string(argv[i]);
    }
    // Now process the args
    if (std::find(args.begin(), args.end(), "-h") != args.end()) {
        help();
    }
    if (std::find(args.begin(), args.end(), "-v") != args.end()) {
        verbose = true;
    }
    if (std::find(args.begin(), args.end(), "-b") != args.end()) {
        blender = true;
    }
    auto svg_name = get_name("-o", args);
    auto cam_name = get_name("-c", args);
    auto vert_name = get_name("-m", args);
    print_info("Intializing data....");
    std::shared_ptr<alpha::Camera> cam_inst;
    if (std::find(args.begin(), args.end(), "-t") != args.end()) {
        cam_inst = std::make_shared<alpha::Camera>(cam_name, true);
    } else {
        cam_inst = std::make_shared<alpha::Camera>(cam_name);
    }
    alpha::SVG_export svg(cam_inst->img_width, cam_inst->img_height, svg_name);
    alpha::mesh_data data(vert_name, blender);
    print_info("Done.");
    if (verbose) {
        cam_inst->print_info();
        std::cout << "Number of triangles : " << data.num_triangles
                  << std::endl;
    }
    if (std::find(args.begin(), args.end(), "-z") != args.end()) {
        alpha::Rasteriser<> rast(cam_inst);
        for (uint32_t i = 0; i < data.num_triangles; i++) {
            const auto &v0 = data.vertices[3 * i];
            const auto &v1 = data.vertices[3 * i + 1];
            const auto &v2 = data.vertices[3 * i + 2];
            if (rast.draw_triangle(v0, v1, v2)) {
                alpha::math::Vec3f v0_rast, v1_rast, v2_rast;
                cam_inst->convert_to_raster(v0, v0_rast);
                cam_inst->convert_to_raster(v1, v1_rast);
                cam_inst->convert_to_raster(v2, v2_rast);
                svg.put_line(v0_rast, v1_rast);
                svg.put_line(v1_rast, v2_rast);
                svg.put_line(v2_rast, v0_rast);
            }
        }

    } else {
        for (uint32_t i = 0; i < data.num_triangles; i++) {
            const auto &v0 = data.vertices[3 * i];
            const auto &v1 = data.vertices[3 * i + 1];
            const auto &v2 = data.vertices[3 * i + 2];
            alpha::math::Vec3f v0_rast, v1_rast, v2_rast;
            cam_inst->convert_to_raster(v0, v0_rast);
            cam_inst->convert_to_raster(v1, v1_rast);
            cam_inst->convert_to_raster(v2, v2_rast);
            svg.put_line(v0_rast, v1_rast);
            svg.put_line(v1_rast, v2_rast);
            svg.put_line(v2_rast, v0_rast);
        }
    }
}
