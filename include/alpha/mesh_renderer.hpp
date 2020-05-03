//===---- mesh_renderer ----- Vertex mesh renderer --------------*- C++ -*-===//
//
// Alpha-trace -> Minimal C++ raytracer
//
// Written by: Shikhar Bhardwaj | shikhar@bluefog.me
//
//===----------------------------------------------------------------------===//
///
/// \file
/// Render a vertex mesh to an SVG
///
//===----------------------------------------------------------------------===//
#ifndef ALPHA_MESH_RENDERER
#define ALPHA_MESH_RENDERER

#include <alpha/camera.hpp>
#include <alpha/rasteriser.hpp>
#include <alpha/svg.hpp>
#include <alpha/vertex_import.hpp>

namespace alpha {
    struct MeshRenderer {
        std::string _mesh_data_file;
        std::string _camera_file;
        std::string _output_file;
        bool _cull_back_faces;
        bool _y_up;

        // Camera
        std::shared_ptr<alpha::Camera> _cam_inst = std::make_shared<alpha::Camera>(_camera_file);

        // Rasteriser
        alpha::Rasteriser<> _rast = alpha::Rasteriser<>(_cam_inst);

        // SVG Export
        std::unique_ptr<alpha::SVG_export> _exporter = std::make_unique<alpha::SVG_export>(
            _cam_inst->img_width, _cam_inst->img_height, _output_file);

        // Mesh data
        alpha::mesh_data _data = alpha::mesh_data(_mesh_data_file, _y_up);

        MeshRenderer() = delete;

        MeshRenderer(std::string mesh_data_file, std::string camera_file,
            std::string output_file, bool cull_back_faces, bool y_up) :
            _mesh_data_file(mesh_data_file), _camera_file(camera_file),
            _output_file(output_file), _cull_back_faces(cull_back_faces),
            _y_up(y_up) {}

        void render() {
            for (uint32_t i = 0; i < _data.num_triangles; ++i) {
                const auto& v0 = _data.vertices[3 * i];
                const auto& v1 = _data.vertices[3 * i + 1];
                const auto& v2 = _data.vertices[3 * i + 2];

                if (!_cull_back_faces || _rast.draw_triangle(v0, v1, v2)) {
                    alpha::math::Vec3f v0_rast, v1_rast, v2_rast;
                    _cam_inst->convert_to_raster(v0, v0_rast);
                    _cam_inst->convert_to_raster(v1, v1_rast);
                    _cam_inst->convert_to_raster(v2, v2_rast);
                    _exporter->put_line(v0_rast, v1_rast);
                    _exporter->put_line(v1_rast, v2_rast);
                    _exporter->put_line(v2_rast, v0_rast);
                }
            }
        }
    };
}
#endif
