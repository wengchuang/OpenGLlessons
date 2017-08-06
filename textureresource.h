#ifndef TEXTURERESOURCE_H
#define TEXTURERESOURCE_H
#include <map>
#include <string>
#include "iresourceitem.h"
#include "commonutil.h"
class   Texture2dId
    {
    public:
    Texture2dId()
    {
        _texture    =   0;
        _width      =   0;
        _height     =   0;
        _user       =   0;
    }
    unsigned    _texture;
    unsigned    _width;
    unsigned    _height;
    void*       _user;
};


class TextureResource : public IResourceItem
{
    typedef std::map<std::string,Texture2dId>   TextureMap;
public:
    Texture2dId getTexture(const char* texture);
    int resourceInitialize();
    int resourceUnInitialize();
private:
    Texture2dId createTexture2DFromFile(const char* fileName);
    Texture2dId createTexture2DFromStream( const char* stream,unsigned length );
private:
    TextureMap*          _textureMap;
};

#endif // TEXTURERESOURCE_H
