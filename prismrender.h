#ifndef PRISMRENDER_H
#define PRISMRENDER_H
#include "baserender.h"
#include <glm/glm.hpp>
#include <QVector>

class PrismRender : public BaseRender
{
public:
    PrismRender(const int& pointCnt = 4);
    virtual void onSurfaceChanaged(const GLsizei& width,const GLsizei& height);
    virtual ~PrismRender();
protected:
    virtual void onUpdate(Shader* shader,
                          const glm::mat4& pvMat,
                          const glm::mat4& modelMat);
private:
    QVector<glm::vec3>* mPoints;
    int   mCnt;
};

#endif // PRISMRENDER_H
