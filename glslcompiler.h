#ifndef GLSLCOMPILER_H
#define GLSLCOMPILER_H
#include <QByteArray>
#include <GL/glew.h>
#include <GL/glut.h>

class GLSLCompiler
{
public:
    static GLuint compileFromeFile(const char* vertexFileName,
                              const char* fragmentFileName);
    static GLuint compileFromString(const char* vertexString,
                              const char* fragmentString);
    static void destroyProgram(GLuint programId);
private:
   static GLuint  compile(GLuint type,const char** text);
   static GLuint  linkProgram(GLuint* shaderIds,int size);
   static int     loadSourceFromeFile(const char* fileName,QString& bytes);
};

#endif // GLSLCOMPILER_H
