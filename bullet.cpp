#include "bullet.h"
#include "visionmath.hpp"
#include "absgles2app.h"

Bullet::Bullet(ShaderMap* map,const unsigned long& timeSpec,const int& curTime)
{
    mShaderMap  = map;
    _attrSpeed          =   100;
    _attrMaxDistance    =   200;
    this->timeSpec      = timeSpec;
    this->beginTimes    = curTime;
    this->curTime       = curTime;
    _texture            = AbsGLES2App::getGLESAppContext()->getTextureResource()->getTexture("./data/image/plane1.tex");
}
void Bullet::onRender(int width, int height, const glm::mat4 &pvMat){
    if(Vision::distance(_posSrc,bulletBody.getPosition()) < 25){
        return;
    }
    bulletBody.update();
    //glActiveTexture(GL_TEXTURE0 + 0);
    glBindTexture(GL_TEXTURE_2D,_texture._texture);

    glm::vec2    halfSz  =   bulletBody.getSize() * 0.5f;

    glm::vec3    vMin    =   -glm::vec3 (halfSz.x,halfSz.y,0);
    glm::vec3    vMax    =   glm::vec3 (halfSz.x,halfSz.y,0);
    float vert[]   =
    {
        vMin.x,vMin.y,0,    0,0,
        vMax.x,vMin.y,0,    1,0,
        vMin.x,vMax.y,0,    0,1,
        vMax.x,vMax.y,0,    1,1
    };
    static GLint matRef = mShaderMap->getUniformRef("pvmMat");
    static GLint textureRef = mShaderMap->getUniformRef("_texture");

    glm::mat4   mvp     =   pvMat * bulletBody.getMatrix();
    glUniformMatrix4fv(matRef, 1, false, &mvp[0][0]);
    glUniform1i(textureRef,0);
    glVertexAttribPointer(0,  3,  GL_FLOAT,   false,  5*sizeof(float),vert);
    glVertexAttribPointer(1,  2,  GL_FLOAT,   false, 5*sizeof(float),&vert[3]);

    glDrawArrays(GL_TRIANGLE_STRIP,0,4);
}
bool Bullet::isDead()
{
    return  Vision::distance(_posSrc,bulletBody.getPosition()) >= _attrMaxDistance;
}
void Bullet::setPosition(const glm::vec3& pos)
{
    _posSrc =   pos;
    bulletBody.setPosition(pos);
}

void Bullet::setMaxDistance(float dist)
{
    _attrMaxDistance    =   dist;
}

void Bullet::setSpeed(float speeed)
{
   _attrSpeed  =   speeed;
}
void Bullet::setSize(const glm::vec2& Size){
    bulletBody.setSize(Size);
}
void Bullet::setDir(const glm::vec3& dir)
{
   _dir    =   dir;
}

void Bullet::update()
{
  glm::vec3 pos = bulletBody.getPosition();
  pos    +=  _dir * (_attrSpeed * (this->curTime-this->beginTimes));
  bulletBody.setPosition(pos);
}
