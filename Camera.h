// Camera.h
// -- viewing and perspective transformations
// cs541 9/18

#ifndef CS541_CAMERA_H
#define CS541_CAMERA_H


#include <glm/glm.hpp>


namespace cs541 {

glm::mat4 view(const glm::vec4 &eye, const glm::vec4 &look, const glm::vec4 &rup);

glm::mat4 perspective(float fov, float aspect, float near);

glm::mat4 perspective(float fov, float aspect, float near, float far);

}


#endif

