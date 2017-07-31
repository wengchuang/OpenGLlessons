#include "shader.h"
#include "glslcompiler.h"
#include <QDebug>

Shader::Shader()
{
    int i=0;
    programId = 0;
    for(i=0;i<NUM_UNIFORM;i++){
        mUniforms[i] = 0;
    }
    for(i = 0;i<MAX_DESC;i++){
        attributes[i] = 0xff;
    }
}


int Shader::setPVMmatrix(const glm::mat4& pvmat){

    if(programId > 0){
        glUniformMatrix4fv(mUniforms[PVM_U],1,GL_FALSE,&pvmat[0][0]);
    }
    return 0;
}

int Shader::shaderInit(const ShaderInfo* info){
    int ret = -1;
    qDebug()<<"shader init begin...";
    qDebug()<<"vsfileName:"<<info->vsfileName;
    qDebug()<<"fsfileName:"<<info->fsfileName;
    programId = GLSLCompiler::compileFromeFile(info->vsfileName,info->fsfileName);
    qDebug()<<"programId:"<<programId;
    if(programId == 0){
        return ret;
    }
    qDebug()<<"compile end...";
    bindVertexAtrributes((VertexLocDesc**)(info->vertexDescs));
    bindUniforms((UniformLocDesc**)(info->uniformDescs));
    return 0;
}
int Shader::bindUniforms(UniformLocDesc**uniformDescs){
    UniformLocDesc*tmp = uniformDescs[0];
    GLuint matRef;
    for(int i= 0;i<MAX_DESC;i++ ){
        tmp = uniformDescs[i];
        if(tmp){
            matRef = glGetUniformLocation( programId, tmp->name );
            if(tmp->type == UniformLocDesc::TYPE_FOR_PVM){
               mUniforms[PVM_U] =  matRef;
            }
        }else{
            break;
        }
    }
    return 0;
}


void Shader::enableVertexAttributeArrays(){
    for(int i = 0;i<MAX_DESC;i++){
        if(attributes[i] != 0xff){
            glEnableVertexAttribArray(attributes[i]);
        }else{
            break;
        }
    }
}
void Shader::disableVertexAttributeArrays(){
    for(int i = 0;i<MAX_DESC;i++){
        if(attributes[i] != 0xff){
            glDisableVertexAttribArray(attributes[i]);
        }else{
            break;
        }
    }
}

int Shader::bindVertexAtrributes( VertexLocDesc**vertexDescs){
    VertexLocDesc*tmp;
    for(int i= 0;i<MAX_DESC;i++ ){
        tmp = vertexDescs[i];
        if(tmp){
            glBindAttribLocation(programId, tmp->local,  tmp->name);
            attributes[i] = tmp->local;
        }else{
            break;
        }

    }
    return 0;

}


Shader::~Shader(){
    for(int i=0;i<NUM_UNIFORM;i++){
        mUniforms[i] = 0;
    }
    if(programId > 0){
        GLSLCompiler::destroyProgram(programId);
    }
}
