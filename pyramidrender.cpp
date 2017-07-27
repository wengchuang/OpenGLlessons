#include "pyramidrender.h"
#include <QDebug>
#define PI (3.1415926f)

PyramidRender::PyramidRender(const int& cnt)
{
    mRadius = 3;
    mCnt = cnt;
    mPoints = new QVector<glm::vec3>(mCnt+2);
}
void PyramidRender::onRender()
{
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glBindVertexArray(getVertArrObj());
    glDrawArrays(GL_TRIANGLE_FAN,0,mPoints->size());
    glBindVertexArray(0);

}
void PyramidRender::onSurfaceChanaged(const GLsizei &width, const GLsizei &height){

    mRadius = (float) width/height*2;

    GLfloat spec = (GLfloat)2*PI/(GLfloat)(mCnt);

    for(int i=1;i< mCnt+1;i++){

        float y = mRadius*glm::sin(spec*i);
        float x = mRadius*glm::cos(spec*i);
        float z = -500.f;
        mPoints->replace(i,glm::vec3(x,y,z));
    }
    mPoints->replace(0,glm::vec3(0,0,-100.f));
    mPoints->replace(mCnt+1,mPoints->at(1));

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
PyramidRender::~PyramidRender(){
    delete mPoints;
}
