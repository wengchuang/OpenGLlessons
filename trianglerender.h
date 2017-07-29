#ifndef TRIANGLEMESH_H
#define TRIANGLEMESH_H
#include "baserender.h"
#include <QDebug>

class TriangleRender : public BaseRender
{
public:
    TriangleRender();
    virtual void onSurfaceChanaged(const GLsizei &width, const GLsizei &height);
protected:
    virtual void onUpdate(Shader* shader,
                          const glm::mat4& pvMat,
                          const glm::mat4& modelMat);
private:
    GLfloat mVertices[9];

};

#endif // TRIANGLEMESH_H
