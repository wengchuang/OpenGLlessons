#include "bullet.h"
#include "visionmath.hpp"
#include "absgles2app.h"
#include <QDebug>

Bullet::Bullet(ShaderMap* map,  FrameItem* parent ):FrameItem(map,parent)
{
    _posSrc = getPosition();
    _attrSpeed          =   100;
    _attrMaxDistance    =   200;
    _texture            = AbsGLES2App::getGLESAppContext()->getTextureResource()->getTexture("./data/image/plane1.tex");
}
void Bullet::onDrawSelf(const Vision::FrameEvent& _event,const glm::mat4&pvMat){
#if 1

    glActiveTexture(GL_TEXTURE0 + 0);
    glBindTexture(GL_TEXTURE_2D,_texture._texture);

    glm::vec2    halfSz  =   this->getSize() * 0.5f;

    glm::vec3    vMin    =   -glm::vec3 (halfSz.x,halfSz.y,0);
    glm::vec3    vMax    =   glm::vec3 (halfSz.x,halfSz.y,0);

    float vert[]   =
    {
        vMin.x,vMin.y,0, 1.0f,   0,0,
        vMax.x,vMin.y,0, 1.0f,   1,0,
        vMin.x,vMax.y,0, 1.0f,   0,1,
        vMax.x,vMax.y,0, 1.0f,   1,1
    };

    static GLint matRef = getShaderMap()->getUniformRef("pvmMat");
    static GLint textureRef = getShaderMap()->getUniformRef("_texture");

    glm::mat4   mvp     =   pvMat * this->getMatrix();
    glUniformMatrix4fv(matRef, 1, false, &mvp[0][0]);
    glUniform1i(textureRef,0);
    glVertexAttribPointer(getShaderMap()->getVertexRef("position"),  4,  GL_FLOAT,   false,  6*sizeof(float),vert);
    glVertexAttribPointer(getShaderMap()->getVertexRef("_uv"),  2,  GL_FLOAT,   false, 6*sizeof(float),&vert[4]);

    glDrawArrays(GL_TRIANGLE_STRIP,0,4);

#endif

}
bool Bullet::isDead()
{
    return  Vision::distance(_posSrc,this->getPosition()) >= _attrMaxDistance;
}


void Bullet::setMaxDistance(float dist)
{
    _attrMaxDistance    =   dist;
}

void Bullet::setSpeed(float speeed)
{
   _attrSpeed  =   speeed;
}

void Bullet::setDir(const glm::vec3& dir)
{
   _dir    =   dir;
}
void Bullet::updatePos(const float& elasped){
    glm::vec3 pos = this->getPosition();
    pos    +=  _dir * (_attrSpeed * elasped);
    this->setPosition(pos);
    update();
}

