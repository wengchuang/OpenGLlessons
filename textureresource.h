#ifndef TEXTURERESOURCE_H
#define TEXTURERESOURCE_H
#include <map>
#include <string>
#include <string.h>
#include <assert.h>
#include "iresourceitem.h"
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
class   ImageHeader
{
protected:
    int     _width;
    int     _height;
    int     _length;
public:
    ImageHeader()
    {
        _width  =   0;
        _height =   0;
        _length =   0;
    }
    /**
    *   宽度
    */
    int    getWidth() const
    {
        return  _width;
    }
    /**
    *   高度
    */
    int    getHeight() const
    {
        return  _height;
    }
    int    getLength() const
    {
        return  _length;
    }
};
class CELLImageReader
    {
    public:
        class   FileHeader
        {
        public:
            char    _magic[16];
            char    _format[32];
        };
    public:
        CELLImageReader(char* data,int length)
            :_data(data)
            ,_length(length)
            ,_curPtr(0)
        {
        }
        bool    parse()
        {
            memcpy(&_header,_data,sizeof(_header));

            if (strcmp(_header._magic,"CELL.Image") != 0)
            {
                return  false;
            }
            else
            {
                _curPtr +=  sizeof(_header);
                return  true;
            }
        }
        char*   getFormat()
        {
            return  _header._format;
        }

        void    clear()
        {
            _curPtr =   0;
        }
        char*   getCursor()
        {
            return  _data + _curPtr;
        }
        void    skip(int length)
        {
            _curPtr +=  length;
        }
        bool    eof()
        {
            assert(_curPtr <= _length);
            return  _curPtr >= _length;
        }
    protected:
        FileHeader  _header;
        char*       _data;
        int         _curPtr;
        int         _length;
};

class TextureResource : public IResourceItem
{
    typedef std::map<std::string,Texture2dId>   TextureMap;
public:
    Texture2dId getTexture(char* texture);
    int resourceInitialize();
    int resourceUnInitialize();
private:
    Texture2dId createTexture2DFromFile(const char* fileName);
    Texture2dId createTexture2DFromStream( const char* stream,unsigned length );
private:
    TextureMap          _textureMap;
};

#endif // TEXTURERESOURCE_H
