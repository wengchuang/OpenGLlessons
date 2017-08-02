#ifndef COMMONUTIL_H
#define COMMONUTIL_H
#include <GL/glew.h>
#include <GL/glu.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>
namespace CommonUtils {
    //
    char*readFile(const char* fileName,unsigned& length);

    GLenum getInternalFormat(const char* fmt);
    GLenum getSrcType(const char* fmt);
    GLenum getSrcFormat(const char* fmt);



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
}
#endif // COMMONUTIL_HPP
