#include "glslcompiler.h"
#include <QFile>
#include <QDebug>
#include <QTextStream>
#include <QString>

int GLSLCompiler::loadSourceFromeFile(const char* fileName,QString& textString){
    int ret = -1;
    QFile file(fileName);
    if(!file.open(QIODevice::ReadOnly)){
        qDebug()<<"open "<<fileName<<"error";
        return ret;
    }
    QTextStream is(&file);
    textString = is.readAll();
    file.close();
    ret = 0;
    return ret;

}
GLuint GLSLCompiler::compileFromeFile(const char* vertexFileName,
                          const char* fragmentFileName){
    GLuint Result = 0;
    QString vertexText,fragmentText;
    if(loadSourceFromeFile(vertexFileName,vertexText)== -1){
        return Result;
    }
    if(loadSourceFromeFile(fragmentFileName,fragmentText)== -1){
        return Result;
    }
    return compileFromString(vertexText.toLocal8Bit().data() ,
                             fragmentText.toLocal8Bit().data());
}
GLuint GLSLCompiler::compileFromString(const char* vertexString,
                          const char* fragmentString){
    GLuint ids[2];
    ids[0] = compile(GL_VERTEX_SHADER,&vertexString);
    if(ids[0] == 0){
        qDebug()<<"compile "<<vertexString <<"failed";
        return ids[0];
    }

    ids[1] = compile(GL_FRAGMENT_SHADER,&fragmentString);
    if(ids[1] == 0){
        qDebug()<<"compile "<<fragmentString <<"failed";
        return ids[1];
    }

    return linkProgram(ids,2);

}

GLuint  GLSLCompiler::compile(GLuint type,const char** text){
    GLuint ret = 0;
    GLint res;
    int InfoLogLength;
    GLuint shaderId = glCreateShader(type);
    glShaderSource(shaderId,1,(const GLchar**)text,NULL);
    glCompileShader(shaderId);
    glGetShaderiv(shaderId, GL_COMPILE_STATUS, &res);;
    glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if ( InfoLogLength > 0 ){
            QVector<char> VertexShaderErrorMessage(InfoLogLength+1);
            glGetShaderInfoLog(shaderId, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
            qDebug()<<(&VertexShaderErrorMessage[0]);
    }else{
        ret = shaderId;
    }
    return ret;
}
GLuint  GLSLCompiler::linkProgram(GLuint* shaderIds,int size){
    int i = 0;
    GLint Result = GL_FALSE;
    int InfoLogLength;
    GLuint proShaderId = glCreateProgram();
    for(i = 0;i< size;i++){
        glAttachShader(proShaderId, shaderIds[i]);
    }

    glLinkProgram(proShaderId);

    // Check the program
    glGetProgramiv(proShaderId, GL_LINK_STATUS, &Result);
    glGetProgramiv(proShaderId, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if ( InfoLogLength > 0 ){
        QVector<char> ProgramErrorMessage(InfoLogLength+1);
        glGetProgramInfoLog(proShaderId, InfoLogLength, NULL, &ProgramErrorMessage[0]);
        qDebug()<<(&ProgramErrorMessage[0]);
    }

    for(i = 0;i< size;i++){
        glDetachShader(proShaderId, shaderIds[i]);
        glDeleteShader(shaderIds[i]);
    }

    if(Result == GL_FALSE){
        proShaderId = 0;
    }
    return proShaderId;
}



void GLSLCompiler::destroyProgram(GLuint programId){
    if(programId > 0){
        glDeleteProgram(programId);
    }
}
