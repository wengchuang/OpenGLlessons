#include "shader.h"
#include <QFile>
#include <QDebug>
#include <QTextStream>
static struct ShaderInfo infos[]={
{"./mesh.vs",GL_VERTEX_SHADER},
{"./mesh.fs",GL_FRAGMENT_SHADER}
};

Shader::Shader():proShaderId(0)
{
    for(int i=0;i<NUM_UNIFORM;i++){
        mUniforms[i] = 0;
    }
}

GLuint Shader::compileFile(const ShaderInfo& info){
    int ret = 0;
    QString text;
    char* context;
    GLuint shaderId = glCreateShader(info.ShaderType);
    QFile file(info.fileName);
    if(!file.open(QIODevice::ReadOnly)){
        qDebug()<<"open "<<info.fileName<<"error";
        return ret;
    }
    QTextStream is(&file);
    GLint Result = GL_FALSE;
    int InfoLogLength;

    text = is.readAll();
    context = text.toLocal8Bit().data();

    glShaderSource(shaderId,1,(const GLchar**)&context,NULL);
    glCompileShader(shaderId);

    glGetShaderiv(shaderId, GL_COMPILE_STATUS, &Result);;
    glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if ( InfoLogLength > 0 ){
            QVector<char> VertexShaderErrorMessage(InfoLogLength+1);
            glGetShaderInfoLog(shaderId, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
            qDebug()<<(&VertexShaderErrorMessage[0]);
     }
    if(Result != GL_FALSE){
        ret = shaderId;
    }
    file.close();
    return ret;
}
GLuint  Shader::linkProgram(GLuint* shaderIds,int size){
    int i = 0;
    GLint Result = GL_FALSE;
    int InfoLogLength;
    proShaderId = glCreateProgram();
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

const GLuint& Shader::loadShaderProgram(const QList<ShaderInfo*>& infos){
    if(proShaderId > 0){
        destroyProgram();
    }

    int i = 0;
    QVector<GLuint> shaderIds(infos.size());
    for(i=0;i<size;i++){
        shaderIds[i] = compileFile(infos[i]);
        if(shaderIds[i] == 0){
            return proShaderId;
        }

    }
    proShaderId =linkProgram(shaderIds.data(),size);
    if(proShaderId > 0){
       mUniforms[TRANSFORM_U] = glGetUniformLocation( proShaderId, "g_matModelMaxtix");
       mUniforms[PROJECTION_U] = glGetUniformLocation( proShaderId,"g_matViewProjMaxtix");
       qDebug()<<"shader init ok!\n";
    }
    return proShaderId;
}
#if 0
void Shader::update(const Transform& transForm,const Camera& camera){

    if(proShaderId > 0){
        glm::mat4 proj = camera.getViewProjection();
        glUniformMatrix4fv(mUniforms[PROJECTION_U],1,GL_FALSE,&proj[0][0]);

        glm::mat4 model = transForm.getModelMatrix();
        glUniformMatrix4fv(mUniforms[TRANSFORM_U],1,GL_FALSE,&model[0][0]);

    }

}
#endif
int Shader::shaderInit(const QList<ShaderInfo*>& infos){
    int ret = -1;
    if(loadShaderProgram(infos) > 0){
        ret = 0;
    }
    return ret;
}

void Shader::destroyProgram(){
    if(proShaderId >0){
        glDeleteProgram(proShaderId);
    }
    for(int i=0;i<NUM_UNIFORM;i++){
        mUniforms[i] = 0;
    }
    proShaderId = 0;
}

Shader::~Shader(){
    destroyProgram();
}
