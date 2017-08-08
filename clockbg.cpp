#if 1
#include "clockbg.h"
#include "absgles2app.h"
#include "shader.h"
#include "clockpointer.h"

ClockBg::ClockBg(ShaderMap* shaderMap,FrameItem* parent ):FrameItem(shaderMap,parent)
{
    clockBg =   AbsGLES2App::getGLESAppContext()->getTextureResource()->getTexture("./data/image/background.tex");

    glm::vec2 size = glm::vec2(clockBg._width,clockBg._height);
    this->setSize(size);
    this->setPosition(glm::vec3(200,200,0));
    ClockPointer * pointer = new ClockPointer(shaderMap,this);
    glm::vec3 pos = glm::vec3(size.x/2,size.y/2,.0f);
    pointer->setpos(pos);

}

void ClockBg::onDrawSelf(const Vision::FrameEvent&ev,const glm::mat4& pvMat){
#if 1
    glActiveTexture(GL_TEXTURE0 + 0);
    glBindTexture(GL_TEXTURE_2D,clockBg._texture);
    static float scale =0.0f;
    static bool  scaleFlag = false;

    if(!scaleFlag){
        if(scale < 0.3f){
            scale += 0.001f;
        }else{
           scaleFlag = !scaleFlag;
        }
    }else{

        if(scale > -0.3f){
            scale -= 0.001f;
        }else{
           scaleFlag = !scaleFlag;
        }
    }

    if(!scaleFlag){
        this->delatPos(glm::vec3(.0f,scale*1.2,.0f));

    }else{
        this->delatPos(glm::vec3(.0f,-scale*1.2,.0f));

    }

    this->setScale(glm::vec3(1.0f  + scale,1.0f + scale,1.0f));
    //this->setPosition(glm::vec3(100,500,.0f));
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
    static GLint matRef = getShaderMap()->getUniformRef("pvmMat");
    static GLint textureRef = getShaderMap()->getUniformRef("_texture");
    glm::mat4   mvp     =   pvMat * this->getMatrix();
    glUniformMatrix4fv(matRef, 1, false, &mvp[0][0]);
    glUniform1i(textureRef,0);
    glVertexAttribPointer(getShaderMap()->getVertexRef("position"), 4,  GL_FLOAT,   false,  6*sizeof(float),vert);
    glVertexAttribPointer(getShaderMap()->getVertexRef("_uv"),  2,  GL_FLOAT,   false, 6*sizeof(float),&vert[4]);
    glDrawArrays(GL_TRIANGLE_STRIP,0,4);
#endif
#if 0
    glActiveTexture(GL_TEXTURE0 + 0);
    glBindTexture(GL_TEXTURE_2D,pointerBg._texture);

     halfSz  =   _pointerBody.getSize() * 0.5f;

     vMin    =   -glm::vec3 (halfSz.x,halfSz.y,0);
     vMax    =   glm::vec3 (halfSz.x,halfSz.y,0);
    static float angle = 0;
    float vert1[]   =
    {
        vMin.x,vMin.y,0, 1.0f,   0,0,
        vMax.x,vMin.y,0, 1.0f,   1,0,
        vMin.x,vMax.y,0, 1.0f,   0,1,
        vMax.x,vMax.y,0, 1.0f,   1,1
    };
    angle =ev._frameTime*45;
    _pointerBody.setRoteZ(angle);
    pos = _pointerBody.getPosition();
    if(!scaleFlag){
        pos.y += scale*1.2;
    }else{
        pos.y -= scale*1.2;
    }
    _pointerBody.setPosition(pos);
    _pointerBody.setScale(glm::vec3(1.0f  + scale,1.0f + scale,1.0f));
    _pointerBody.update();


    mvp     =   pvMat * _pointerBody.getMatrix();
    glUniformMatrix4fv(matRef, 1, false, &mvp[0][0]);
    glUniform1i(textureRef,0);
    glVertexAttribPointer(getShaderMap()->getVertexRef("position"), 4,  GL_FLOAT,   false,  6*sizeof(float),vert1);
    glVertexAttribPointer(getShaderMap()->getVertexRef("_uv"),  2,  GL_FLOAT,   false, 6*sizeof(float),&vert1[4]);
    glDrawArrays(GL_TRIANGLE_STRIP,0,4);
#endif
}
#endif
