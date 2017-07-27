#include "trianglemesh.h"
#include <QDebug>
GLfloat vertices[] = {
    -1.0f,-1.0f,2.0f,
    1.0f,-1.0f,2.0f,
    0.0f,1.0f,2.0f,
};
TriangleMesh::TriangleMesh()
{
    memcpy(mVertices,vertices,sizeof(mVertices));
}
void TriangleMesh::onResize(const GLsizei &width, const GLsizei &height)
{
    Q_UNUSED(width);
    Q_UNUSED(height);
    const GLuint&  VBO = getVertArrBuffer(Mesh::POSITION_VB);
    const GLuint&  VAO = getVertArrObj();
#if 0
    GLfloat value = getRatio();
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
#endif





    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER,VBO);
    glBufferData(GL_ARRAY_BUFFER,sizeof(mVertices),mVertices,GL_STATIC_DRAW);


    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3*sizeof(GLfloat),(GLvoid*)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER,0);
    glBindVertexArray(0);
}
void TriangleMesh::onRender(){
    glBindVertexArray(getVertArrObj());
    glDrawArrays(GL_TRIANGLES,0,3);
    glBindVertexArray(0);

}
