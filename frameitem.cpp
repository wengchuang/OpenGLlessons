#include "frameitem.h"

void FrameItem::setpos(glm::vec3& pos){
    glm::vec3 scenePos = pos;
    if(mParent){
        glm::vec3 parentPos = mParent->getPosition();
        glm::vec2 size = mParent->getSize();
        scenePos += parentPos-glm::vec3(size.x*0.5,size.y*0.5,.0f);
    }
    mpos = pos;
    this->setPosition(scenePos);
}
void FrameItem::onRender(const FrameEvent&ev,const glm::mat4&mat){
    onDrawSelf(ev,mat);
    drawChildren(ev,mat);
}

void FrameItem::drawChildren(const FrameEvent&ev,const glm::mat4&mat){
    std::vector<FrameItem*>::iterator itr = this->begin();
    for(;itr != this->end();++itr){
        FrameItem* item = *itr;
        item->onRender(ev,mat);
    }

}
