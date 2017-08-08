#ifndef FRAMEITEM_H
#define FRAMEITEM_H
#include "iglinput.h"
#include "IRenderable.h"
#include "shader.h"
#include "visionnode.h"
#include <vector>
using namespace Vision;

class FrameItem : public Vision::VisionNode,
                  public std::vector<FrameItem*>,
                  public IGLInput,
                  public IModelRenderable
{
public:
    FrameItem(ShaderMap* shaderMap,FrameItem* parent = 0){
        mShaderMap = shaderMap;
        mParent = NULL;
        mpos = glm::vec3(0.0f,0.0f,0.0f);
        if(parent){
            mParent = parent;
            parent->addChild(this);
        }
        setpos(mpos);

    }
    virtual inline void setScale(const glm::vec3& scale){
        VisionNode::setScale(scale);
        std::vector<FrameItem*>::iterator itr = this->begin();
        for(;itr != this->end();++itr){
            FrameItem* item = *itr;
            item->setScale(scale);
        }

    }
    virtual inline void delatPos(const glm::vec3& pos){
        VisionNode::delatPos(pos);
        std::vector<FrameItem*>::iterator itr = this->begin();
        for(;itr != this->end();++itr){
            FrameItem* item = *itr;
            item->delatPos(pos);
        }
    }
    virtual inline void  setRoteX(const float& angle)
    {
        VisionNode::setRoteX(angle);
        std::vector<FrameItem*>::iterator itr = this->begin();
        for(;itr != this->end();++itr){
            FrameItem* item = *itr;
            item->setRoteX(angle);
        }

    }
    virtual inline void  setRoteY(const float& angle)
    {
        VisionNode::setRoteY(angle);
        std::vector<FrameItem*>::iterator itr = this->begin();
        for(;itr != this->end();++itr){
            FrameItem* item = *itr;
            item->setRoteY(angle);
        }
    }
    virtual inline void  setRoteZ(const float& angle)
    {
        VisionNode::setRoteZ(angle);
        std::vector<FrameItem*>::iterator itr = this->begin();
        for(;itr != this->end();++itr){
            FrameItem* item = *itr;
            item->setRoteZ(angle);
        }
    }
    const FrameItem*const  getParent(){
        return mParent;
    }
    virtual inline void setPosition(const glm::vec3& pos)
    {
        VisionNode::setPosition(pos);
        resetChildrenpos();
    }
    void setpos(glm::vec3& pos);
    inline const glm::vec3& getpos(){
        return mpos;
    }

    int addChild(FrameItem* child){
        int ret  = -1;
        if(child){
            this->push_back(child);
        }
        return ret;
    }
    void onRender(const Vision::FrameEvent &,const glm::mat4&);
    virtual ~FrameItem(){}
    virtual void    onMouseMove(int /*absx*/, int /*absy*/, int/*absz*/){}
    /**
    *   鼠标按下
    */
    virtual void    onMousePress(int /*absx*/, int /*absy*/, MouseButton /*id*/){}
    /**
    *   鼠标双击
    */
    virtual void    onMouseDbPress(int /*absx*/, int /*absy*/, MouseButton /*id*/){}
    /**
    *   鼠标释放
    */
    virtual void    onMouseRelease(int /*absx*/, int /*absy*/, MouseButton /*id*/){}
    /**
    *   键盘按下
    */
    virtual void    onKeyPress(KeyCode /*key*/, int /*text*/){}
    /**
    *   键盘抬起
    */
    virtual void    onKeyRelease(KeyCode /*key*/){ }
    /**
    *   输入
    */
    virtual void onChar(int /*ch*/) {}

protected:
    void resetChildrenpos(){
        std::vector<FrameItem*>::iterator itr = this->begin();
        for(;itr != this->end();++itr){
            FrameItem* item = *itr;
            glm::vec3 pos = item->getpos();
            item->setpos(pos);
        }
    }
    virtual void onDrawSelf(const FrameEvent&,const glm::mat4&) = 0;
    inline ShaderMap* getShaderMap(){
        return mShaderMap;
    }
private:
    void drawChildren(const FrameEvent&,const glm::mat4&);
private:
    ShaderMap* mShaderMap;
    FrameItem* mParent;
    glm::vec3 mScenePos;
    glm::vec3 mpos;

};

#endif // FRAMEITEM_H
