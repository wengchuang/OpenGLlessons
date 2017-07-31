#include "trianglerender.h"
#include <glm/gtx/transform.hpp>
#include <QDebug>


TriangleRender::TriangleRender()
{

    onSurfaceChanaged(800,600);
}
void TriangleRender::onSurfaceChanaged(const GLsizei &width, const GLsizei &height)
{
    GLfloat value = (float)width/height;
    GLfloat mYValue = 1.0f;

    mVertices[0] = -value;
    mVertices[1] = -mYValue;
    mVertices[2] = -200.0;


    mVertices[3] = value;
    mVertices[4] = -mYValue;
    mVertices[5] = -200.0;

    mVertices[6] = 0.0;
    mVertices[7] = mYValue;
    mVertices[8] = -200.0;
    glVertexAttribPointer (0,3,GL_FLOAT, GL_FALSE, 0, mVertices );


}

void TriangleRender::onUpdate(Shader* shader,
                      const glm::mat4& pvMat,
                      const glm::mat4& modelMat){
    glm::mat4 mat = pvMat*modelMat;
    shader->setPVMmatrix(mat);
    glDrawArrays( GL_TRIANGLES, 0, 3 );
}


