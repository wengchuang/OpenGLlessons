#include "player.h"
#include "absgles2app.h"
#include "shader.h"
#include <typeinfo>
#include <GL/glew.h>
#include <GL/glu.h>
#include "visionmath.hpp"

player::player(ShaderMap* shaderMap):FrameItem(shaderMap)
{
    _plant =   AbsGLES2App::getGLESAppContext()->getTextureResource()->getTexture("./data/image/plane1.tex");
    glm::vec2 size = glm::vec2(_plant._width,_plant._height);
    _nodeBody.setSize(size);
    _nodeBody.setPosition(glm::vec3(200,100,0));
    mShaderMap = shaderMap;
    bLeftPress = false;
    times      = 0;
    mTimer = new Timer(200);
    mTimer->setTimerFun(this,&player::addBullet);
    AbsGLES2App::getGLESAppContext()->getTimerManagerResource()->registerTimer(mTimer);

}
void player::addBullet(){
    times++;
    Bullet* bullet  =   new Bullet(mShaderMap,200,times);
    bullet->setPosition(_nodeBody.getPosition());
    bullet->setDir(glm::vec3(0,-1,0));
    bullet->setSize(glm::vec2(20,20));
    bullet->setMaxDistance(500);
    bullet->setSpeed(5);
    bulletList.push_back(bullet);

    glm::vec3 pos = _nodeBody.getPosition();
    bullet  =   new Bullet(mShaderMap,200,times);
    pos.x += (_nodeBody.getSize() * 0.5f).x;
    bullet->setPosition(pos);
    bullet->setDir(glm::vec3(-0.5,-1,0));
    bullet->setSize(glm::vec2(16,16));
    bullet->setMaxDistance(500);
    bullet->setSpeed(5.0f);
    bulletList.push_back(bullet);


    pos = _nodeBody.getPosition();
    bullet  =   new Bullet(mShaderMap,200,times);
    pos.x -= (_nodeBody.getSize() * 0.5f).x;
    bullet->setPosition(pos);
    bullet->setDir(glm::vec3(0.5,-1,0));
    bullet->setSize(glm::vec2(16,16));
    bullet->setMaxDistance(500);
    bullet->setSpeed(3.0f);
    bulletList.push_back(bullet);
}
void player::setPos(glm::vec3& pos){
    _nodeBody.setPosition(pos);
}
void player::renderChildren(const glm::mat4& pvMat){
    BulletList::iterator itr = bulletList.begin();
    for ( ;itr != bulletList.end() ; )
    {
       Bullet* bullet  =   *itr;
       bullet->setTimes(times);
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
       bullet->onRender(0,0,pvMat);
    }
}
void player::onRender(int width,int height,const glm::mat4& pvMat){

    glActiveTexture(GL_TEXTURE0 + 0);
    glBindTexture(GL_TEXTURE_2D,_plant._texture);

    _nodeBody.update();
    glm::vec2    halfSz  =   _nodeBody.getSize() * 0.5f;

    glm::vec3    vMin    =   -glm::vec3 (halfSz.x,halfSz.y,0);
    glm::vec3    vMax    =   glm::vec3 (halfSz.x,halfSz.y,0);
    float vert[]   =
    {
        vMin.x,vMin.y,0,    0,0,
        vMax.x,vMin.y,0,    1,0,
        vMin.x,vMax.y,0,    0,1,
        vMax.x,vMax.y,0,    1,1
    };

    glm::mat4   mvp     =   pvMat * _nodeBody.getMatrix();
    glUniformMatrix4fv(mShaderMap->getUniformRef("pvmMat"), 1, false, &mvp[0][0]);
    glUniform1i(mShaderMap->getUniformRef("_texture"),0);
    glVertexAttribPointer(0,  3,  GL_FLOAT,   false,  5*sizeof(float),vert);
    glVertexAttribPointer(1,  2,  GL_FLOAT,   false, 5*sizeof(float),&vert[3]);
    glDrawArrays(GL_TRIANGLE_STRIP,0,4);
    renderChildren(pvMat);

}

void player::onChar(int ch){
    glm::vec3 pos;

    switch(ch){
    case 'a' :
    case 'A' :
        pos = _nodeBody.getPosition();
        pos.x -= 10;
        setPos(pos);
        break;
    case 'd' :
    case 'D' :
        pos = _nodeBody.getPosition();
        pos.x += 10;
       setPos(pos);
        break;

    case 'w' :
    case 'W' :
        pos = _nodeBody.getPosition();
        pos.y -= 10;
        setPos(pos);
        break;


    case 's' :
    case 'S' :

        pos = _nodeBody.getPosition();
        pos.y += 10;
        setPos(pos);
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
        setPos(pos);
        bLeftPress =false;
    }
}
void player::onMouseMove(int x, int y , int z){
    if(bLeftPress){
        glm::vec3 pos = glm::vec3(x,y,z);
        setPos(pos);
    }
}

player::~player(){
    delete mTimer;
    for(BulletList::iterator it  = bulletList.begin(); it != bulletList.end(); )
    {
         Bullet* bullet  =   *it;
         it = bulletList.erase(it);
         delete bullet;
    }
}
