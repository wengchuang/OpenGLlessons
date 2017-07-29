#include "prismrender.h"
#include <QDebug>
#define PI (3.1415926f)
PrismRender::PrismRender(const int& pointCnt)
{
    mPoints = new QVector<glm::vec3>();
    mCnt = pointCnt;
    mPoints->resize((mCnt+1)*2*2);
}
void vec3toFloats(const QVector<glm::vec3>& vector,GLfloat* floats){
    for(int i=0;i<vector.size();i++){
        glm::vec3 value = vector.at(i);
        floats[3*i] = value.x;
        floats[3*i+1] = value.y;
        floats[3*i+2] = value.z;
    }
}
void PrismRender::onSurfaceChanaged(const GLsizei& width,const GLsizei& height){
    GLfloat mRadius = (float) width/height/2;
    GLfloat spec = (GLfloat)2*PI/(GLfloat)(mCnt);
    glm::vec3 point;
    int index = -1;
    for(int i=0;i<(mCnt);i++){
        GLfloat x = mRadius*glm::sin(spec*i);
        GLfloat y = mRadius*glm::cos(spec*i);
        point = glm::vec3(x,y,-500);
        index++;

        mPoints->replace(2*(mCnt+1)+index/2,point);
        mPoints->replace(index,point);
        point = glm::vec3(x,y,-200);
        index++;
        mPoints->replace(3*(mCnt+1)+index/2,point);
        mPoints->replace(index,point);

    }
    index++;


    mPoints->replace(2*(mCnt+1)+index/2,mPoints->at(0));
    mPoints->replace(index,mPoints->at(0));
    index++;

    mPoints->replace(3*(mCnt+1)+index/2,mPoints->at(1));
    mPoints->replace(index,mPoints->at(1));

    glVertexAttribPointer (0,3,GL_FLOAT, GL_FALSE, 3*sizeof(GLfloat), mPoints->data() );
}

void PrismRender::onUpdate(Shader* shader,
                      const glm::mat4& pvMat,
                      const glm::mat4& modelMat){
    shader->setPVMmatrix(pvMat,modelMat);
    glEnableVertexAttribArray (0);
    glDrawArrays(GL_TRIANGLE_FAN, 0, mPoints->size() );
    glDisableVertexAttribArray(0);


}

PrismRender::~PrismRender(){
    delete mPoints;
}
