#include "player.h"
#include "absgles2app.h"
#include "shader.h"
#include <typeinfo>
#include <GL/glew.h>
#include <GL/glu.h>

player::player(ShaderMap* shaderMap):FrameItem(shaderMap)
{
    _plant =   AbsGLES2App::getGLESAppContext()->getTextureResource()->getTexture("./data/image/plane1.tex");
    glm::vec2 size = glm::vec2(_plant._width,_plant._height);
    _nodeBody.setSize(size);
    _nodeBody.setPosition(glm::vec3(200,100,0));
    _nodeBody.update();
    mShaderMap = shaderMap;
    bLeftPress = false;
}
void player::setPos(glm::vec3& pos){
    _nodeBody.setPosition(pos);
}
void player::onRender(int width,int height,const glm::mat4& pvMat){

    glActiveTexture(GL_TEXTURE0 + 0);
    glBindTexture(GL_TEXTURE_2D,_plant._texture);

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

}
