#ifndef GLESFRAME_H
#define GLESFRAME_H
#include "frameitem.h"
#include "absglframe.h"
#include "shader.h"
#include <vector>

class GLESFrame : public AbsGLFrame
{
    friend class GLESFrameGenerator;
public:
    int frameInit(const int& mWidth,const int& mHeight);
    virtual ~GLESFrame();
    virtual void onRender(const Vision::FrameEvent&);
    virtual void onRender(const int& width,const int& height,const Vision::FrameEvent&);
    virtual void onMouseMove(int absx, int absy, int  absz);

    virtual void onMousePress(int absx, int absy, MouseButton id);
    /**
    *   鼠标双击
    */
    virtual void onMouseDbPress(int absx, int absy, MouseButton id);
    /**
    *   鼠标释放
    */
    virtual void onMouseRelease(int absx, int absy, MouseButton id);
    /**
    *   键盘按下
    */
    virtual void onKeyPress(KeyCode key, int text);
    /**
    *   键盘抬起
    */
    virtual void onKeyRelease(KeyCode key);
    /**
    *   输入
    */
    virtual void onChar(int ch);

protected:
    GLESFrame();

protected:
    inline Shader* getShader(){
        return mShader;
    }
    virtual int onFrameInit(){return 0;}
    virtual ShaderInfo* onLoadShaderInfo(){return NULL;}
    virtual void renderSelf(const Vision::FrameEvent&){}
    inline ShaderMap* getShaderMap(){
        return mShaderMap;
    }
    virtual glm::mat4& onGetPVMat(){
        static glm::mat4 mat(1.0);
       return mat;
    }
    void addChild(FrameItem* item);

protected:
    int  mWidth ;
    int  mHeight;
private :
      Shader *mShader;
      ShaderMap*mShaderMap;
      typedef std::vector<FrameItem*>   ChildList;
      ChildList  childs;

};

#endif // GLESFRAME_H
