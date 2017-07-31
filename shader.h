#ifndef SHADERLODER_H
#define SHADERLODER_H
#include <GL/glew.h>
#include <GL/glut.h>
#include <glm/glm.hpp>
#include <QDebug>

#define MAX_DESC 8

struct VertexLocDesc{
    GLuint      local;
    const char* name;
};
struct UniformLocDesc{
    enum UniformType{
        TYPE_FOR_NORMAL,
        TYPE_FOR_PVM
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
        qDebug()<<"11111111111111111111";
        if(programId > 0){
            qDebug()<<"programId..............."<<programId;
            glUseProgram(programId);
            qDebug()<<"2222222222222222222222";
            //enableVertexAttributeArrays();
            ret = 0;
        }
        qDebug()<<"@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@";
        return ret;
    }
    inline int unbindShader(){
        int ret = -1;
        if(programId > 0){
            disableVertexAttributeArrays();
            //glUseProgram(0);
            ret = 0;
        }
        return ret;
    }
    int shaderInit(const ShaderInfo* info);
    int setPVMmatrix(const glm::mat4& pvmat);
    virtual ~Shader();

private:
    int bindVertexAtrributes(VertexLocDesc**vertexDescs);
    int bindUniforms(UniformLocDesc**uniformDescs);

    void enableVertexAttributeArrays();
    void disableVertexAttributeArrays();

private:
    enum{
        PVM_U,
        NUM_UNIFORM
    };
    GLuint programId;
    GLuint attributes[MAX_DESC];
    GLuint mUniforms[NUM_UNIFORM];
};

#endif // SHADERLODER_H
