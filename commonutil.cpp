#include"commonutil.h"

char*CommonUtils::readFile(const char* fileName,unsigned& length)
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
        printf(buffer);
        assert(pFile != 0);
    }
    return  0;

}

GLenum  CommonUtils::getInternalFormat(const char* fmt)
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

GLenum CommonUtils::getSrcType(const char* fmt)
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
GLenum CommonUtils::getSrcFormat(const char* fmt)
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



