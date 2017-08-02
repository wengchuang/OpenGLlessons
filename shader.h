#ifndef SHADERLODER_H
#define SHADERLODER_H
#include <GL/glew.h>
#include <GL/glut.h>
#include <glm/glm.hpp>
#include <list>
#include <QDebug>
#include <map>
using namespace std;
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
        if(fileName != NULL){
            strncpy(this->vsfileName,fileName,sizeof(this->vsfileName));
        }
    }
    inline void setFsFileName(const char*fileName){
        if(fileName){
            strncpy(this->fsfileName,fileName,sizeof(this->fsfileName));
        }
    }
    inline int addVertex(const char*name){
        int ret = -1;
        if(vertexIndex < MAX_DESC){
            if(sizeof(this->vertexNames[vertexIndex]) > strlen(name)){
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
            if(sizeof(this->uniformsNames[uniformsIndex]) > strlen(name)){
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
public:
   inline GLint getVertexRef(const char* name){
        GLint ret = -1;
        std::map<std::string,GLint>::iterator itr = vertexMap.find(std::string(name));
        if(itr != vertexMap.end())
        {
            ret = itr->second;
        }
        return ret;
   }

   inline GLint getUniformRef(const char* name){
       GLint ret = -1;
       std::map<std::string,GLint>::iterator itr = uniformMap.find(std::string(name));
       if(itr != uniformMap.end())
       {
           ret = itr->second;
       }
       return ret;
   }
private:
    friend class Shader;
    inline void setVertexMapValue(char*name,GLint value){
        vertexMap.insert(make_pair(name,   value));
    }
    inline void setUniformMapValue(char*name,GLint value){
        uniformMap.insert(make_pair(name,   value));
    }
    inline void clear(){
        vertexMap.clear();
        uniformMap.clear();
    }
    std::map<std::string,GLint> vertexMap;
    std::map<std::string,GLint> uniformMap;
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
    ShaderMap* shaderInit( ShaderInfo* info);
    inline ShaderMap* getShaderMap(){
        return mShaderMap;
    }
    virtual ~Shader();

private:
    int bindVertexAtrributes(ShaderInfo* info);
    int bindUniforms(ShaderInfo* info);


    void enableVertexAttributeArrays();
    void disableVertexAttributeArrays();

private:
    ShaderMap* mShaderMap;
    GLuint programId;
};

#endif // SHADERLODER_H
