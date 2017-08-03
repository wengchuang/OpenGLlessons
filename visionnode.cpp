#include "visionnode.h"
namespace Vision{
VisionNode::VisionNode(void* user)
{
    pos = glm::vec3(0,0,0);
    scale = glm::vec3(1,1,1);
    rote = glm::vec3(0,0,0);
    local = getModelMatrix();
    glm::vec2 size = glm::vec2(8,8);
    setSize(size);
    user = user;
}
void VisionNode::setSize(glm::vec2& size){
    mSize = size;
    glm::vec3 minPos = -glm::vec3(size.x*0.5f,size.y*0.5f,0.0f);
    glm::vec3 maxPos = glm::vec3(size.x*0.5f,size.y*0.5f,0.0f);
    alBox.setExtents(minPos,maxPos);
    alBox.transform(local);
}
void VisionNode::update()
{
    local  =   getModelMatrix();
    setSize(mSize);
}

}
