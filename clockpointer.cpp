#include "clockpointer.h"
#include "absgles2app.h"
ClockPointer::ClockPointer(ShaderMap* shaderMap,FrameItem* parent):FrameItem(shaderMap,parent)
{
    pointerBg = AbsGLES2App::getGLESAppContext()->getTextureResource()->getTexture("./data/image/needle.tex");
    glm::vec2 size = glm::vec2(pointerBg._width,pointerBg._height);
    this->setSize(size);
}
void ClockPointer::onDrawSelf(const Vision::FrameEvent&ev,const glm::mat4& pvMat){
    glActiveTexture(GL_TEXTURE0 + 0);
    glBindTexture(GL_TEXTURE_2D,pointerBg._texture);

     glm::vec2 halfSz  =   this->getSize() * 0.5f;

    glm::vec3 vMin    =   -glm::vec3 (halfSz.x,halfSz.y,0);
    glm::vec3  vMax    =   glm::vec3 (halfSz.x,halfSz.y,0);

    float vert1[]   =
    {
        vMin.x,vMin.y,0, 1.0f,   0,0,
        vMax.x,vMin.y,0, 1.0f,   1,0,
        vMin.x,vMax.y,0, 1.0f,   0,1,
        vMax.x,vMax.y,0, 1.0f,   1,1
    };
    float angle =ev._frameTime*45;
    this->setRoteZ(angle);
    this->update();
    static GLint matRef = getShaderMap()->getUniformRef("pvmMat");
    static GLint textureRef = getShaderMap()->getUniformRef("_texture");


    glm::mat4 mvp     =   pvMat * this->getMatrix();
    glUniformMatrix4fv(matRef, 1, false, &mvp[0][0]);
    glUniform1i(textureRef,0);
    glVertexAttribPointer(getShaderMap()->getVertexRef("position"), 4,  GL_FLOAT,   false,  6*sizeof(float),vert1);
    glVertexAttribPointer(getShaderMap()->getVertexRef("_uv"),  2,  GL_FLOAT,   false, 6*sizeof(float),&vert1[4]);
    glDrawArrays(GL_TRIANGLE_STRIP,0,4);
}
