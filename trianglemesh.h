#ifndef TRIANGLEMESH_H
#define TRIANGLEMESH_H
#include "mesh.h"
#include <QDebug>

class TriangleMesh : public Mesh
{
public:
    TriangleMesh();
protected:
    virtual void onRender();
    virtual void onResize(const GLsizei &width, const GLsizei &height);
private:
    GLfloat mVertices[9];

};

#endif // TRIANGLEMESH_H
