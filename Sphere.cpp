// Sphere.cpp
// cs541 8/17


#include <iostream>

#include <cmath>
#include "Sphere.h"
using namespace std;


const float PI = 4.0f * atan(1.0f);


#define M (2*size)
#define N (size)
#define NORTH (M*(N-1))
#define SOUTH (M*(N-1)+1)
Sphere::Sphere(int size)
    : vertices(M*(N-1)+2),
      normals(M*(N-1)+2) {
  for (int i=1; i < N; ++i) {
    float theta = PI*i/N;
    for (int j=0; j < M; ++j) {
      int index = M*(i-1)+j;
      float phi = 2*PI*j/M;
      normals[index].x = sin(theta)*cos(phi);
      normals[index].y = sin(theta)*sin(phi);
      normals[index].z = cos(theta);
      normals[index].w = 0;
    }
  }
  normals[NORTH] = glm::vec4(0.0f,0.0f,1.0f,0.0f);
  normals[SOUTH] = glm::vec4(0.0f,0.0f,-1.0f,0.0f);

  for (unsigned n=0; n < normals.size(); ++n) {
    vertices[n] = normals[n];
    vertices[n].w = 1;
  }

  for (int i=2; i < N; ++i) {
    for (int j=0; j < M; ++j) {
      Face face;
      int jp1 = (j+1)%M;
      face[0] = M*(i-2) + j;
      face[1] = M*(i-2) + jp1;
      face[2] = M*(i-1) + jp1;
      faces.push_back(face);
      face[1] = face[2];
      face[2] = M*(i-1) + j;
      faces.push_back(face);
    }
  }
  for (int j=0; j < M; ++j) {
    Face face;
    int jp1 = (j+1)%M;
    face[0] = j;
    face[1] = jp1;
    face[2] = NORTH;
    faces.push_back(face);
    face[0] = M*(N-2) + j;
    face[1] = M*(N-2) + jp1;
    face[2] = SOUTH;
    faces.push_back(face);
  }

}
#undef SOUTH
#undef NORTH
#undef N
#undef M


int Sphere::vertexCount(void) {
  return vertices.size();
}


glm::vec4* Sphere::vertexArray(void) {
  return &(vertices[0]);
}


glm::vec4* Sphere::normalArray(void) {
  return &(normals[0]);
}


int Sphere::faceCount(void) {
  return faces.size();
}


Mesh3D::Face* Sphere::faceArray(void) {
  return &(faces[0]);
}

