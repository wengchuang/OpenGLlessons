#include "shader.h"
#include "glslcompiler.h"
#include <QDebug>

Shader::Shader()
{
    programId = 0;
    mShaderMap= NULL;

}


ShaderMap* Shader::shaderInit(ShaderInfo* info){
    programId = GLSLCompiler::compileFromeFile(info->getVsFileName(),info->getFsFileName());
    if(programId == 0){
        return NULL;
    }
    if(mShaderMap){
        mShaderMap->clear();
    }else{
        mShaderMap = new ShaderMap;
    }
    bindVertexAtrributes(info);
    bindUniforms(info);
    return mShaderMap;
}
int Shader::bindUniforms(ShaderInfo* info){
    GLuint matRef;
    for(int i= 0;i<MAX_DESC;i++ ){
        char* str = info->getUniformName(i);
        if(str){
            matRef = glGetUniformLocation(programId, str);
            mShaderMap->setUniformMapValue(str,matRef);
        }else{
            break;
        }
    }
    return 0;
}


void Shader::enableVertexAttributeArrays(){
    std::map<std::string,GLint>::iterator it = mShaderMap->vertexMap.begin();
    std::map<std::string,GLint>::iterator endIt = mShaderMap->vertexMap.end();;
    for(; it!=endIt; it++){
       glEnableVertexAttribArray(it->second);
    }
}
void Shader::disableVertexAttributeArrays(){
    std::map<std::string,GLint>::iterator it = mShaderMap->vertexMap.begin();
    std::map<std::string,GLint>::iterator endIt = mShaderMap->vertexMap.end();;
    for(; it!=endIt; it++){
       glDisableVertexAttribArray(it->second);
    }
}

int Shader::bindVertexAtrributes(ShaderInfo* info){

    GLuint vertexRef;
    for(int i= 0;i<MAX_DESC;i++ ){
        char* str = info->getVertexName(i);
        if(str){
            vertexRef = glGetAttribLocation(programId,str);
            mShaderMap->setVertexMapValue(str,vertexRef);
        }else{
            break;
        }
    }
    return 0;
}


Shader::~Shader(){
    if(programId > 0){
        GLSLCompiler::destroyProgram(programId);
    }
    delete mShaderMap;
}
