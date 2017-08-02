#include "textureresource.h"

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
    char*       buffer  =   CommonUtils::readFile(fileName,length);
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
    CommonUtils::CELLImageReader reader((char*)stream,(int)length);
    if (!reader.parse())
    {
        return  texId;
    }

    glGenTextures(1, &texId._texture);
    glBindTexture(GL_TEXTURE_2D, texId._texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);


    CommonUtils::ImageHeader*header  =   (CommonUtils::ImageHeader*)reader.getCursor();
    texId._width        =   (unsigned)header->getWidth();
    texId._height       =   (unsigned)header->getHeight();


    GLenum  intFormat   =   CommonUtils::getInternalFormat(reader.getFormat());
    GLenum  srcType     =   CommonUtils::getSrcType(reader.getFormat());
    GLint   srcFmt      =   CommonUtils::getSrcFormat(reader.getFormat());
    GLint   level       =   0;
    while(!reader.eof())
    {
        header  =   (CommonUtils::ImageHeader*)reader.getCursor();
        reader.skip(sizeof(CommonUtils::ImageHeader));
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
