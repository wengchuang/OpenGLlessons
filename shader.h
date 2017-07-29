#ifndef SHADERLODER_H
#define SHADERLODER_H
#include <GL/glew.h>
#include <GL/glut.h>
#include <glm/glm.hpp>

#define MAX_DESC 8

struct VertexLocDesc{
    GLuint      local;
    const char* name;
};
struct UniformLocDesc{
    enum UniformType{
        TYPE_FOR_NORMAL,
        TYPE_FOR_PV,
        TYPE_FOR_M
    };
    const char* name;
    UniformType type;
};

struct ShaderInfo{
    const char* vsfileName;
    const char* fsfileName;
    VertexLocDesc*vertexDescs[MAX_DESC];
    UniformLocDesc*uniformDescs[MAX_DESC];

};

class Shader
{
public:
    Shader();
    inline int bindShader(){
        int ret = -1;
        if(programId > 0){
            glUseProgram(programId);
            ret = 0;
        }
        return ret;
    }
    int shaderInit(const ShaderInfo* info);
    int setPVMmatrix(const glm::mat4& pvmat,const glm::mat4& modelMat);
    virtual ~Shader();

private:
    int bindVertexAtrributes(VertexLocDesc**vertexDescs);
    int bindUniforms(UniformLocDesc**uniformDescs);
private:
    enum{
        TRANSFORM_U,
        PROJECTION_U,
        NUM_UNIFORM
    };
    GLuint programId;
    GLuint mUniforms[NUM_UNIFORM];
};

#endif // SHADERLODER_H
