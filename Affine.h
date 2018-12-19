// Affine.h
// -- basic transformations, using core GLM (hw study)
// cs541 8/18

#ifndef CS541_AFFINE_H
#define CS541_AFFINE_H


#include <glm/glm.hpp>


namespace cs541 {

glm::mat4 scale(float r);

glm::mat4 scale(float rx, float ry, float rz);

glm::mat4 translate(const glm::vec4& v);

glm::mat4 rotate(float t, const glm::vec4& v);

glm::mat4 transpose3x3(const glm::mat4& A);

glm::vec4 cross(const glm::vec4 &u, const glm::vec4 &v);

}


#endif

