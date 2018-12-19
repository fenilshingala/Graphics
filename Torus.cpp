// torus.cpp
// -- generate a torus mesh
// jsh 8/17

#include <fstream>
#include <cmath>
#include "Torus.h"
using namespace std;


Torus::Torus(float thickness, int size)
    : vertex_count(size*size),
      face_count(2*vertex_count) {
  const float PI = 4.0f*atan(1.0f);
  float major_radius = 1.0f/(1.0f+thickness),
        minor_radius = thickness*major_radius;

  vertices = new glm::vec4[vertex_count];
  for (int j=0; j < size; ++j) {
    float phi = 2*PI*j/size;
    for (int i=0; i < size; ++i) {
      int index = size*j + i;
      float theta = 2*PI*i/size,
            rho = major_radius + minor_radius*cos(theta);
      vertices[index].x = rho*cos(phi);
      vertices[index].y = rho*sin(phi);
      vertices[index].z = minor_radius*sin(theta);
      vertices[index].w = 1;
    }
  }

  normals = new glm::vec4[vertex_count];
  for (int j=0; j < size; ++j) {
    float phi = 2*PI*j/size;
    for (int i=0; i < size; ++i) {
      int index = size*j + i;
      float theta = 2*PI*i/size;
      normals[index].x = cos(theta)*cos(phi);
      normals[index].y = cos(theta)*sin(phi);
      normals[index].z = sin(theta);
      normals[index].w = 0;
    }
  }

  faces = new Face[face_count];
  for (int j=0; j < size; ++j) {
    int jp1 = (j+1)%size;
    for (int i=0; i < size; ++i) {
      int index = 2*(size*j+i),
          ip1 = (i+1)%size;
      faces[index][0] = size*j+i;
      faces[index][1] = size*jp1+i;
      faces[index][2] = size*jp1+ip1;
      faces[index][3] = faces[index][0];
      faces[index][4] = faces[index][2];
      faces[index][5] = size*j+ip1;
    }
  }

}


Torus::~Torus(void) {
  delete[] faces;
  delete[] normals;
  delete[] vertices;
}


int Torus::vertexCount(void) {
  return vertex_count;
}


glm::vec4* Torus::vertexArray(void) {
  return vertices;
}


glm::vec4* Torus::normalArray(void) {
  return normals;
}


int Torus::faceCount(void) {
  return face_count;
}


Mesh3D::Face* Torus::faceArray(void) {
  return faces;
}

