#include "prismrender.h"
#include <QDebug>
#define PI (3.1415926f)
PrismRender::PrismRender(const int& pointCnt)
{
    mPoints = new QVector<glm::vec3>();
    mCnt = pointCnt;
    mPoints->resize((mCnt+1)*2*2);
}
void PrismRender::onRender(){
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glBindVertexArray(getVertArrObj());
    glDrawArrays(GL_TRIANGLE_FAN,0,mPoints->size());
    glBindVertexArray(0);

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
        point = glm::vec3(x,y,-100);
        index++;

        mPoints->replace(2*(mCnt+1)+index/2,point);
        mPoints->replace(index,point);
        point = glm::vec3(x,y,-10);
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


    const GLuint&  VBO = getVertArrBuffer(BaseRender::POSITION_VB);
    const GLuint&  VAO = getVertArrObj();
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER,VBO);
    glBufferData(GL_ARRAY_BUFFER,mPoints->size()*sizeof(glm::vec3),mPoints->data(),GL_STATIC_DRAW);


    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3*sizeof(GLfloat),(GLvoid*)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER,0);
    glBindVertexArray(0);
}
PrismRender::~PrismRender(){
    delete mPoints;
}
