#ifndef SHADERLODER_H
#define SHADERLODER_H
#include <GL/glew.h>
#include <GL/glut.h>
#include "transform.h"
#include "camera.h"


struct ShaderInfo{
    const char* fileName;
    GLint ShaderType;
};

class Shader
{
public:
    Shader();
    inline int bindShader(){
        int ret = -1;
        if(proShaderId > 0){
            glUseProgram(proShaderId);
            ret = 0;
        }
        return ret;
    }
    int shaderInit();
    virtual void update(const Transform& transForm,
                        const Camera& camera);
    virtual ~Shader();
protected:
    virtual int onShaderInit();
private:
    const GLuint& loadShaderProgram(ShaderInfo* infos,int size);
    GLuint  compileFile(const ShaderInfo& info);
    GLuint  linkProgram(GLuint* shaderIds,int size);
    void destroyProgram();
private:
    enum{
        TRANSFORM_U,
        PROJECTION_U,
        NUM_UNIFORM
    };
    GLuint proShaderId;
    GLuint mUniforms[NUM_UNIFORM];
};

#endif // SHADERLODER_H
