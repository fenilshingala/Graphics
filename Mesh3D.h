// Mesh3D.h
// -- triangular 3D mesh iterface
// cs541 8/18

#ifndef CS541_MESH3D_H
#define CS541_MESH3D_H

#include <glm/glm.hpp>


class Mesh3D {
  public:
    virtual ~Mesh3D(void) { }
    virtual int vertexCount(void) = 0;
    virtual glm::vec4* vertexArray(void) = 0;
    virtual glm::vec4* normalArray(void) = 0;
    virtual int faceCount(void) = 0;
    struct Face {
      unsigned index[3];
      unsigned operator[](int i) const { return index[i]; }
      unsigned& operator[](int i) { return index[i]; }
    };
    virtual Face* faceArray(void) = 0;
};


#endif

