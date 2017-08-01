#include "textureresource.h"
#include <string.h>
#include <stdio.h>
#include <GL/glew.h>
#include <GL/glu.h>
char*	readFile(const char* fileName,unsigned& length)
{
    char    szFile[256];
    sprintf(szFile,"%s",fileName);
    FILE*   pFile  =   fopen(szFile,"rb");
    if (pFile)
    {
        fseek( pFile, 0, SEEK_END );
        length = ftell( pFile );
        fseek(pFile, 0, SEEK_SET );
        char* buffer =   new char[length + 1];
        fread( buffer, 1, length, pFile );
        buffer[length] = 0;
        fclose( pFile );
        return  buffer;
    }
    else
    {
        char    buffer[256];
        sprintf(buffer,"read %s  failed",fileName);
        assert(pFile != 0 && buffer);
    }
    return  0;

}
GLenum  getInternalFormat(const char* fmt)
{
    if (strcmp(fmt,"PIXEL_R8G8B8A8") == 0)
    {
        return  GL_RGBA;
    }
    else if(strcmp(fmt,"PIXEL_R8G8B8") == 0)
    {
        return  GL_RGB;
    }
    else if(strcmp(fmt,"PIXEL_RGBA4") == 0)
    {
        return  GL_RGBA4;
    }
    else if(strcmp(fmt,"PIXEL_A8") == 0)
    {
        return  GL_ALPHA;
    }
    else if(strcmp(fmt,"PIXEL_I8") == 0)
    {
        return  GL_LUMINANCE;
    }
    else if(strcmp(fmt,"PIXEL_IA8") == 0)
    {
        return  GL_LUMINANCE_ALPHA;
    }
    else
    {
        return  GL_RGB;
    }
}

GLenum getSrcType(const char* fmt)
{
   if (strcmp(fmt,"PIXEL_RGBA4") == 0)
   {
       return  GL_UNSIGNED_SHORT_4_4_4_4;
   }
   if (strcmp(fmt,"PIXEL_RGB565") == 0)
   {
       return  GL_UNSIGNED_SHORT_5_6_5;
   }
   else
   {
       return  GL_UNSIGNED_BYTE;
   }
}
GLenum      getSrcFormat(const char* fmt)
{
   if (strcmp(fmt,"PIXEL_R8G8B8A8") == 0)
   {
       return  GL_RGBA;
   }
   else if(strcmp(fmt,"PIXEL_R8G8B8") == 0)
   {
       return  GL_RGB;
   }
   else if(strcmp(fmt,"PIXEL_RGBA4") == 0)
   {
       return  GL_RGBA;
   }
   else if(strcmp(fmt,"PIXEL_RGB565") == 0)
   {
       return  GL_RGB;
   }
   else if(strcmp(fmt,"PIXEL_A8") == 0)
   {
       return  GL_ALPHA;
   }
   else if(strcmp(fmt,"PIXEL_I8") == 0)
   {
       return  GL_LUMINANCE;
   }
   else if(strcmp(fmt,"PIXEL_IA8") == 0)
   {
       return  GL_LUMINANCE_ALPHA;
   }
   else
   {
       return  GL_RGB;
   }
}
Texture2dId TextureResource::getTexture(char* texture){
    TextureMap::iterator itr = _textureMap.find(texture);
    if (itr == _textureMap.end())
    {
        Texture2dId texId   =   createTexture2DFromFile(texture);
        _textureMap[texture]=   texId;
        return      texId;
    }
    else
    {
        return  itr->second;
    }
}
Texture2dId TextureResource::createTexture2DFromFile(const char* fileName){
    Texture2dId texId;
    unsigned    length  =   0;
    char*       buffer  =   readFile(fileName,length);
    if (buffer)
    {
        texId   =   createTexture2DFromStream(buffer,length);
        delete [] buffer;
    }
    return  texId;
}

Texture2dId TextureResource::createTexture2DFromStream( const char* stream,unsigned length )
{
    Texture2dId texId;
    CELLImageReader reader((char*)stream,(int)length);
    if (!reader.parse())
    {
        return  texId;
    }

    glGenTextures(1, &texId._texture);
    glBindTexture(GL_TEXTURE_2D, texId._texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);


    ImageHeader*header  =   (ImageHeader*)reader.getCursor();
    texId._width        =   (unsigned)header->getWidth();
    texId._height       =   (unsigned)header->getHeight();


    GLenum  intFormat   =   getInternalFormat(reader.getFormat());
    GLenum  srcType     =   getSrcType(reader.getFormat());
    GLint   srcFmt      =   getSrcFormat(reader.getFormat());
    GLint   level       =   0;
    while(!reader.eof())
    {
        header  =   (ImageHeader*)reader.getCursor();
        reader.skip(sizeof(ImageHeader));
        char*           pixel   =   reader.getCursor();

        glTexImage2D(
            GL_TEXTURE_2D,
            level,
            intFormat,
            header->getWidth(),
            header->getHeight(),
            0,
            srcFmt,
            srcType,
            pixel
            );
        ++level;
        //int itt = glGetError();
        reader.skip(header->getLength());
    }
    return  texId;
}
int TextureResource::resourceInitialize(){
    return 0;
}
int TextureResource::resourceUnInitialize(){
    return 0;
}
