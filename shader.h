#ifndef SHADERLODER_H
#define SHADERLODER_H
#include <GL/glew.h>
#include <GL/glut.h>
#include <glm/glm.hpp>
#include <list>
#include <QDebug>

#define MAX_DESC 8

class ShaderInfo{
public:
    ShaderInfo(const char* vsFileName = NULL,const char* fsFileName = NULL){
        vertexIndex   = 0;
        uniformsIndex = 0;
        memset(this->vsfileName,0,sizeof(this->vsfileName));
        memset(this->fsfileName,0,sizeof(this->fsfileName));
        memset(this->vertexNames,0,sizeof(this->vertexNames));
        memset(this->uniformsNames,0,sizeof(this->uniformsNames));

        if(vsFileName != NULL){
            strncpy(this->vsfileName,vsFileName,sizeof(this->vsfileName));
        }
        if(fsFileName){
            strncpy(this->fsfileName,fsFileName,sizeof(this->fsfileName));
        }
    }
    inline void setVsFileName(const char*fileName){
        if(vsFileName != NULL){
            strncpy(this->vsfileName,vsFileName,sizeof(this->vsfileName));
        }
    }
    inline void setFsFileName(const char*fileName){
        if(fsFileName){
            strncpy(this->fsfileName,fsFileName,sizeof(this->fsfileName));
        }
    }
    inline int addVertex(const char*name){
        int ret = -1;
        if(vertexIndex < MAX_DESC){
            if(sizeof(this->vertexNames[vertexIndex] > strlen(name))){
                strncpy(this->vertexNames[vertexIndex],name,sizeof(this->vertexNames[vertexIndex]));
                vertexIndex++;
                ret = 0;
            }
        }
        return ret;

    }
    inline int addUniform(const char* name){
        int ret = -1;
        if(uniformsIndex < MAX_DESC){
            if(sizeof(this->uniformsNames[uniformsIndex] > strlen(name))){
                strncpy(this->uniformsNames[uniformsIndex],name,sizeof(this->uniformsNames[uniformsIndex]));
                uniformsIndex++;
                ret = 0;
            }
        }
        return ret;
    }
    inline char* getVsFileName(){
        char* retString = NULL;
        if(strlen(vsfileName) > 0){
            retString =  vsfileName;
        }
        return retString;
    }
    inline char*getFsFileName(){
        char* retString = NULL;
        if(strlen(fsfileName) > 0){
            retString = fsfileName;
        }
        return retString;
    }
    inline char* getVertexName(int index){
        char* retString = NULL;
        if((index >= 0) &&(index < MAX_DESC)){
            if(strlen(vertexNames[index]) > 0){
                retString = vertexNames[index];
            }
        }
        return retString;
    }
    inline char* getUniformName(int index){
        char* retString = NULL;
        if((index >= 0) &&(index < MAX_DESC)){
            if(strlen(uniformsNames[index]) > 0){
                retString = uniformsNames[index];
            }
        }
        return retString;
    }
private:
    unsigned char vertexIndex;
    unsigned char uniformsIndex;
    char vsfileName[32];
    char fsfileName[32];
    char vertexNames[MAX_DESC][10];
    char uniformsNames[MAX_DESC][10];
};

class ShaderMap{
private:
    friend class Shader;
    void setVertexMapValue(char*name,GLint value);
};

class Shader
{
public:
    Shader();
    inline int bindShader(){
        int ret = -1;
        if(programId > 0){
            glUseProgram(programId);
            enableVertexAttributeArrays();
            ret = 0;
        }
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
        NORMAL,
        NUM_UNIFORM
    };
    GLuint programId;
    GLuint attributes[MAX_DESC];
    GLuint mUniforms[NUM_UNIFORM];
};

#endif // SHADERLODER_H
