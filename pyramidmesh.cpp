#include "pyramidmesh.h"
#define PI (3.1415926f)

PyramidMesh::PyramidMesh()
{
    mRadius = 3;

    mPoints[0] = 0.0f;
    mPoints[1] = 0.0f;
    mPoints[2] = 2.0f;
}
void PyramidMesh::onRender()
{
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glBindVertexArray(getVertArrObj());
    glDrawArrays(GL_TRIANGLE_FAN,0,POINTCNT+1);
    glBindVertexArray(0);

}
void PyramidMesh::onResize(const GLsizei &width, const GLsizei &height){
    Q_UNUSED(height);
    Q_UNUSED(width);
    mRadius = getRatio();


    GLfloat spec = (GLfloat)2*PI/(GLfloat)(POINTCNT-1);

    for(unsigned int i=1;i<POINTCNT;i++){
        mPoints[3*i]= mRadius*glm::sin(spec*i);
        mPoints[3*i+1]= mRadius*glm::cos(spec*i);
        mPoints[3*i+2]= -10.f;
    }

    mPoints[3*POINTCNT]= mPoints[3];
    mPoints[3*POINTCNT+1]=  mPoints[4];
    mPoints[3*POINTCNT+2]=  mPoints[5];
    const GLuint&  VBO = getVertArrBuffer(Mesh::POSITION_VB);
    const GLuint&  VAO = getVertArrObj();

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER,VBO);
    glBufferData(GL_ARRAY_BUFFER,sizeof(mPoints),mPoints,GL_STATIC_DRAW);


    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3*sizeof(GLfloat),(GLvoid*)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER,0);
    glBindVertexArray(0);

}
