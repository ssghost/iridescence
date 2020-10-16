#ifndef GLK_POINTCLOUD_BUFFER_HPP
#define GLK_POINTCLOUD_BUFFER_HPP

#include <memory>
#include <vector>
#include <Eigen/Dense>
#include <glk/drawble.hpp>

namespace glk {

struct AuxBufferData {
  std::string attribute_name;
  int dim;
  int stride;
  GLuint buffer;
};

class PointCloudBuffer : public glk::Drawable {
public:
  EIGEN_MAKE_ALIGNED_OPERATOR_NEW
  using Ptr = std::shared_ptr<PointCloudBuffer>;

  PointCloudBuffer(int stride, int num_points);
  PointCloudBuffer(const float* data, int stride, int num_points);
  virtual ~PointCloudBuffer() override;

  void add_color(const float* data, int stride, int num_points);
  void add_buffer(const std::string& attribute_name, int dim, const float* data, int stride, int num_points);

  virtual void draw(glk::GLSLShader& shader) const override;

  GLuint vba_id() const;
  GLuint vbo_id() const;

  int get_aux_size() const;
  const AuxBufferData& get_aux_buffer(int i) const;

private:
  GLuint vao;
  GLuint vbo;
  int stride;
  int num_points;

  std::vector<AuxBufferData> aux_buffers;
};

}  // namespace glk

#endif