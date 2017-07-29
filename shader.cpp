#include "shader.h"
#include "glslcompiler.h"
#include <QDebug>

Shader::Shader()
{
    programId = 0;
    for(int i=0;i<NUM_UNIFORM;i++){
        mUniforms[i] = 0;
    }
}


int Shader::setPVMmatrix(const glm::mat4& pvmat,const glm::mat4& modelMat){

    if(programId > 0){
        glUniformMatrix4fv(mUniforms[PROJECTION_U],1,GL_FALSE,&pvmat[0][0]);
        glUniformMatrix4fv(mUniforms[TRANSFORM_U],1,GL_FALSE,&modelMat[0][0]);

    }

}

int Shader::shaderInit(const ShaderInfo* info){
    int ret = -1;
    qDebug()<<"shader init begin...";
    programId = GLSLCompiler::compileFromeFile(info->vsfileName,
                                  info->fsfileName);
    if(programId == 0){
        return ret;
    }
    qDebug()<<"compile end...";
    bindVertexAtrributes((VertexLocDesc**)(info->vertexDescs));
    bindUniforms((UniformLocDesc**)(info->uniformDescs));
    return 0;
}
int Shader::bindUniforms(  UniformLocDesc**uniformDescs){
    UniformLocDesc*tmp = uniformDescs[0];
    GLuint matRef;
    for(int i= 0;i<MAX_DESC;i++ ){
        tmp = uniformDescs[i];
        if(tmp){
            matRef = glGetUniformLocation( programId, tmp->name );
            if(tmp->type == UniformLocDesc::TYPE_FOR_PV){
               mUniforms[PROJECTION_U] =  matRef;
            }else if(tmp->type == UniformLocDesc::TYPE_FOR_M){
                mUniforms[TRANSFORM_U] =  matRef;
            }
        }else{
            break;
        }
    }
    return 0;
}
int Shader::bindVertexAtrributes( VertexLocDesc**vertexDescs){
    VertexLocDesc*tmp;
    for(int i= 0;i<MAX_DESC;i++ ){
        tmp = vertexDescs[i];
        if(tmp){
            glBindAttribLocation( programId, tmp->local,  tmp->name);
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
