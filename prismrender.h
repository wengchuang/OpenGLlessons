#ifndef PRISMRENDER_H
#define PRISMRENDER_H
#include "baserender.h"
#include <glm/glm.hpp>
#include <QVector>

class PrismRender : public BaseRender
{
public:
    PrismRender(const int& pointCnt = 3);
    virtual void onRender();
    virtual void onSurfaceChanaged(const GLsizei& width,const GLsizei& height);
    virtual ~PrismRender();
private:
    QVector<glm::vec3>* mPoints;
    int   mCnt;
};

#endif // PRISMRENDER_H
