#include "trianglerender.h"
#include <QDebug>
TriangleRender::TriangleRender()
{
}
void TriangleRender::onSurfaceChanaged(const GLsizei &width, const GLsizei &height)
{
    const GLuint&  VBO = getVertArrBuffer(BaseRender::POSITION_VB);
    const GLuint&  VAO = getVertArrObj();

    GLfloat value = (float)width/height;
    GLfloat mYValue = 1.0f;

    mVertices[0] = -value;
    mVertices[1] = -mYValue;
    mVertices[2] = 2.0;


    mVertices[3] = value;
    mVertices[4] = -mYValue;
    mVertices[5] = 2.0;

    mVertices[6] = 0.0;
    mVertices[7] = mYValue;
    mVertices[8] = 2.0;

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER,VBO);
    glBufferData(GL_ARRAY_BUFFER,sizeof(mVertices),mVertices,GL_STATIC_DRAW);


    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3*sizeof(GLfloat),(GLvoid*)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER,0);
    glBindVertexArray(0);
}
void TriangleRender::onRender(){
    glBindVertexArray(getVertArrObj());
    glDrawArrays(GL_TRIANGLES,0,3);
    glBindVertexArray(0);

}
