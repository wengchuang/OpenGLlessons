#ifndef TRIANGLEMESH_H
#define TRIANGLEMESH_H
#include "baserender.h"
#include <QDebug>

class TriangleRender : public BaseRender
{
public:
    TriangleRender();
    virtual void onRender();
    virtual void onSurfaceChanaged(const GLsizei &width, const GLsizei &height);
private:
    GLfloat mVertices[9];

};

#endif // TRIANGLEMESH_H
