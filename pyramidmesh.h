#ifndef PYRAMIDMESH_H
#define PYRAMIDMESH_H
#include <GL/glew.h>
#include <QVector>
#include <glm/glm.hpp>
#include "mesh.h"
class PyramidMesh:public Mesh
{
public:
    PyramidMesh();
protected:
    virtual void onRender();
    virtual void onResize(const GLsizei &width, const GLsizei &height);
private:
    GLuint   mRadius;

    static const     GLuint POINTCNT = 15 ;
    GLfloat   mPoints[3*(POINTCNT+1)];
};

#endif // PYRAMIDMESH_H
