#include "player.h"
#include "absgles2app.h"
#include "shader.h"
#ifdef UBUNTU_WITH_GL
#include <GL/glew.h>
#include <GL/glut.h>
#endif
#ifdef WIN_WITH_OPENGL_ES2
typedef int GLint;
typedef unsigned int GLuint;
#include <gles2/gl2.h>
#endif

player::player(ShaderMap* shaderMap,FrameItem*parent):FrameItem(shaderMap,parent)
{
    _plant =   AbsGLES2App::getGLESAppContext()->getTextureResource()->getTexture("./data/image/plane1.tex");
    glm::vec2 size = glm::vec2(_plant._width,_plant._height);
    this->setSize(size);
    glm::vec3 pos = glm::vec3(100,100,0);
    this->setpos(pos);
    bLeftPress = false;
    mTimer = new Vision::VisionTimer(*(AbsGLES2App::getGLESAppContext()->getTimerManagerResource()),
                                    0.1f);
    mTimer->bind(this,&player::addBullet);
    AbsGLES2App::getGLESAppContext()->getTimerManagerResource()->registerTimer(mTimer);
}
int player::addBullet(Vision::VisionTimer* timer,const float& elapsed ){


    glm::vec2    halfSz  =  this->getSize()* 0.5f;
    glm::vec3   pos= this->getPosition();
    Bullet* bullet  =   new Bullet(getShaderMap());
    bullet->setSrcPos(pos);

    bullet->setDir(glm::vec3(0,-1,0));

    bullet->setSize(glm::vec2(14,14));

    bullet->setMaxDistance(500);

    bullet->setSpeed(1500);
    bulletList.push_back(bullet);

    pos += glm::vec3(-halfSz.x,0,0);
    bullet  =   new Bullet(getShaderMap());
    bullet->setSrcPos(pos);

    bullet->setDir(glm::vec3(0,-1,0));
    bullet->setSize(glm::vec2(10,10));
    bullet->setMaxDistance(400);
    bullet->setSpeed(1200);
    bulletList.push_back(bullet);


    pos += glm::vec3(halfSz.x+halfSz.x,0,0);
    bullet  =   new Bullet(getShaderMap());
    bullet->setSrcPos(pos);

    bullet->setDir(glm::vec3(0,-1,0));
    bullet->setSize(glm::vec2(10,10));
    bullet->setMaxDistance(400);
    bullet->setSpeed(1200);
    bulletList.push_back(bullet);

    return 0;
}

void player::drawBullets(const Vision::FrameEvent&_event,const glm::mat4& pvMat){
    std::vector<Bullet*>::iterator itr = bulletList.begin();
    for(;itr!= bulletList.end();){
        Bullet* bullet = *itr;
        bullet->updatePos(_event._frameTime);
        if(bullet->isDead()){
           itr = bulletList.erase(itr);
           delete bullet;
          // qDebug()<<"earse bullet...";
           continue;
        }
        bullet->onRender(_event,pvMat);
        ++itr;
    }
}
void player::onDrawSelf(const Vision::FrameEvent&_event,const glm::mat4& pvMat){

    glActiveTexture(GL_TEXTURE0 + 0);
    glBindTexture(GL_TEXTURE_2D,_plant._texture);

    this->update();
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
    static GLint matRef =getShaderMap()->getUniformRef("pvmMat");
    static GLint textureRef = getShaderMap()->getUniformRef("_texture");
    glm::mat4   mvp     =   pvMat * this->getMatrix();
    glUniformMatrix4fv(matRef, 1, false, &mvp[0][0]);
    glUniform1i(textureRef,0);
    glVertexAttribPointer(getShaderMap()->getVertexRef("position"), 4,  GL_FLOAT,   false,  6*sizeof(float),vert);
    glVertexAttribPointer(getShaderMap()->getVertexRef("_uv"),  2,  GL_FLOAT,   false, 6*sizeof(float),&vert[4]);
    glDrawArrays(GL_TRIANGLE_STRIP,0,4);
    drawBullets(_event,pvMat);
}

void player::onChar(int ch){
    glm::vec3 pos;

    switch(ch){
    case 'a' :
    case 'A' :
        pos = this->getPosition();
        pos.x -= 10;
        this->setPosition(pos);
        break;
    case 'd' :
    case 'D' :
        pos = this->getPosition();
        pos.x += 10;
       this->setPosition(pos);
        break;

    case 'w' :
    case 'W' :
        pos = this->getPosition();
        pos.y -= 10;
        this->setPosition(pos);
        break;


    case 's' :
    case 'S' :

        pos = this->getPosition();
        pos.y += 10;
        this->setPosition(pos);
        break;
    }
}
void player::onMousePress(int x, int y, MouseButton btnID){
    if(btnID.toValue() == MouseButton::Left){
        glm::vec2 point = glm::vec2(x,y);
        if(this->containPoint(point)){
            bLeftPress = true;
        }
    }
}
void player::onMouseRelease(int x, int y, MouseButton btnID){
    if(bLeftPress && (btnID.toValue() == MouseButton::Left)){
        glm::vec3 pos = glm::vec3(x,y,0);
        this->setPosition(pos);
        bLeftPress =false;
    }
}
void player::onMouseMove(int x, int y , int z){
    if(bLeftPress){
        glm::vec3 pos = glm::vec3(x,y,z);
        this->setPosition(pos);
    }
}

player::~player(){
    //delete mTimer;
#if 1
    for(std::vector<Bullet*>::iterator it  = bulletList.begin(); it != bulletList.end(); )
    {
         Bullet* bullet  =   *it;
         it = bulletList.erase(it);
         delete bullet;
    }
#endif
}
