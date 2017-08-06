#include "player.h"
#include "absgles2app.h"
#include "shader.h"
#include <typeinfo>
#ifdef UBUNTU_WITH_GL
#include <GL/glew.h>
#include <GL/glut.h>
#endif
#ifdef WIN_WITH_OPENGL_ES2
typedef int GLint;
typedef unsigned int GLuint;
#include <gles2/gl2.h>
#endif

player::player(ShaderMap* shaderMap):FrameItem(shaderMap)
{
    _plant =   AbsGLES2App::getGLESAppContext()->getTextureResource()->getTexture("./data/image/plane1.tex");
    glm::vec2 size = glm::vec2(_plant._width,_plant._height);
    _nodeBody.setSize(size);
    _nodeBody.setPosition(glm::vec3(100,100,0));

    mShaderMap = shaderMap;
    bLeftPress = false;
    mTimer = new Vision::VisionTimer(*(AbsGLES2App::getGLESAppContext()->getTimerManagerResource()),
                                     0.1f);
    mTimer->bind(this,&player::addBullet);
    AbsGLES2App::getGLESAppContext()->getTimerManagerResource()->registerTimer(mTimer);
}
int player::addBullet(Vision::VisionTimer* timer,const float& elapsed ){
    glm::vec2    halfSz  =   _nodeBody.getSize() * 0.5f;
    glm::vec3   pos= _nodeBody.getPosition();
    Bullet* bullet  =   new Bullet(mShaderMap);

    bullet->setPosition(pos);
    bullet->setDir(glm::vec3(0,-1,0));
    bullet->setSize(glm::vec2(14,14));
    bullet->setMaxDistance(500);
    bullet->setSpeed(1500);
    bulletList.push_back(bullet);

    glm::vec3 _pos = glm::vec3(pos.x + halfSz.x,pos.y,0);
    bullet  =   new Bullet(mShaderMap);
    bullet->setPosition(_pos);

    bullet->setDir(glm::vec3(0,-1,0));
    bullet->setSize(glm::vec2(10,10));
    bullet->setMaxDistance(400);
    bullet->setSpeed(1200);
    bulletList.push_back(bullet);

    _pos = glm::vec3(pos.x - halfSz.x,pos.y,0);
    bullet  =   new Bullet(mShaderMap);
    bullet->setPosition(_pos);

    bullet->setDir(glm::vec3(0,-1,0));
    bullet->setSize(glm::vec2(10,10));
    bullet->setMaxDistance(400);
    bullet->setSpeed(1200);
    bulletList.push_back(bullet);
    return 0;
}

void player::renderChildren(const Vision::FrameEvent&_event,const glm::mat4& pvMat){
    BulletList::iterator itr = bulletList.begin();
    for ( ;itr != bulletList.end() ; )
    {
       Bullet* bullet  =   *itr;
       if (bullet->isDead())
       {
           itr =   bulletList.erase(itr);
           delete bullet;
           continue;
       }
       else
       {
           ++itr;
       }
       bullet->onRender(_event,pvMat);
    }
}
void player::onRender(const Vision::FrameEvent&_event,const glm::mat4& pvMat){

    glActiveTexture(GL_TEXTURE0 + 0);
    glBindTexture(GL_TEXTURE_2D,_plant._texture);

    _nodeBody.update();
    glm::vec2    halfSz  =   _nodeBody.getSize() * 0.5f;

    glm::vec3    vMin    =   -glm::vec3 (halfSz.x,halfSz.y,0);
    glm::vec3    vMax    =   glm::vec3 (halfSz.x,halfSz.y,0);

    float vert[]   =
    {
        vMin.x,vMin.y,0, 1.0f,   0,0,
        vMax.x,vMin.y,0, 1.0f,   1,0,
        vMin.x,vMax.y,0, 1.0f,   0,1,
        vMax.x,vMax.y,0, 1.0f,   1,1
    };
    static GLint matRef = mShaderMap->getUniformRef("pvmMat");
    static GLint textureRef = mShaderMap->getUniformRef("_texture");
    glm::mat4   mvp     =   pvMat * _nodeBody.getMatrix();
    glUniformMatrix4fv(matRef, 1, false, &mvp[0][0]);
    glUniform1i(textureRef,0);
    glVertexAttribPointer(getShaderMap()->getVertexRef("position"), 4,  GL_FLOAT,   false,  6*sizeof(float),vert);
    glVertexAttribPointer(getShaderMap()->getVertexRef("_uv"),  2,  GL_FLOAT,   false, 6*sizeof(float),&vert[4]);
    glDrawArrays(GL_TRIANGLE_STRIP,0,4);
    renderChildren(_event,pvMat);

}

void player::onChar(int ch){
    glm::vec3 pos;

    switch(ch){
    case 'a' :
    case 'A' :
        pos = _nodeBody.getPosition();
        pos.x -= 10;
        _nodeBody.setPosition(pos);
        break;
    case 'd' :
    case 'D' :
        pos = _nodeBody.getPosition();
        pos.x += 10;
       _nodeBody.setPosition(pos);
        break;

    case 'w' :
    case 'W' :
        pos = _nodeBody.getPosition();
        pos.y -= 10;
        _nodeBody.setPosition(pos);
        break;


    case 's' :
    case 'S' :

        pos = _nodeBody.getPosition();
        pos.y += 10;
        _nodeBody.setPosition(pos);
        break;
    }
}
void player::onMousePress(int x, int y, MouseButton btnID){
    if(btnID.toValue() == MouseButton::Left){
        glm::vec2 point = glm::vec2(x,y);
        if(_nodeBody.containPoint(point)){
            bLeftPress = true;
        }
    }
}
void player::onMouseRelease(int x, int y, MouseButton btnID){
    if(bLeftPress && (btnID.toValue() == MouseButton::Left)){
        glm::vec3 pos = glm::vec3(x,y,0);
        _nodeBody.setPosition(pos);
        bLeftPress =false;
    }
}
void player::onMouseMove(int x, int y , int z){
    if(bLeftPress){
        glm::vec3 pos = glm::vec3(x,y,z);
        _nodeBody.setPosition(pos);
    }
}

player::~player(){
    //delete mTimer;
    for(BulletList::iterator it  = bulletList.begin(); it != bulletList.end(); )
    {
         Bullet* bullet  =   *it;
         it = bulletList.erase(it);
         delete bullet;
    }
}
