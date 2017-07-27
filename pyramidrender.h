#ifndef PYRAMIDMESH_H
#define PYRAMIDMESH_H
#include <GL/glew.h>
#include <QVector>
#include <glm/glm.hpp>
#include "baserender.h"
class PyramidRender:public BaseRender
{
public:
    PyramidRender(const int& cnt =5);
    virtual void onRender();
    virtual void onSurfaceChanaged(const GLsizei &width, const GLsizei &height);
    ~PyramidRender();
private:
    GLuint   mRadius;
    QVector<glm::vec3> *mPoints;
    int  mCnt;
};

#endif // PYRAMIDMESH_H
