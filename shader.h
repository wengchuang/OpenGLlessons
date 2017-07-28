#ifndef SHADERLODER_H
#define SHADERLODER_H
#include <GL/glew.h>
#include <GL/glut.h>
#include "meshaccessory.h"

struct ShaderInfo{
    const char* fileName;
    GLint ShaderType;
};

class Shader : public MeshAccessory
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
    int shaderInit(const QList<ShaderInfo*>&infos);

    virtual ~Shader();

private:
    const GLuint& loadShaderProgram(const QList<ShaderInfo*>& infos);
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
