#ifndef FRAMEITEM_H
#define FRAMEITEM_H
#include "iglinput.h"
#include "IRenderable.h"
#include "shader.h"

class FrameItem : public IGLInput,public Vision::IModelRenderable
{
public:
    FrameItem(ShaderMap* shaderMap){
        mShaderMap = shaderMap;
    }
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
    inline ShaderMap* getShaderMap(){
        return mShaderMap;
    }
private:
    ShaderMap* mShaderMap;

};

#endif // FRAMEITEM_H
