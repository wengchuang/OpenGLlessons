#ifndef GLESAPPCONTEXT_H
#define GLESAPPCONTEXT_H
class IResourceItem;
#include "textureresource.h"

class GLESAppContext
{
public:
    enum RESOURCETYPE{
        TEXTURE_RESOURCE,
        NUM_RESOURCE
    };
    ~GLESAppContext();
public:
    inline TextureResource* getTextureResource(){
        return (TextureResource*)Resources[TEXTURE_RESOURCE];
    }
private:
    friend class AbsGLES2App;
    GLESAppContext();

private:
    IResourceItem* Resources[NUM_RESOURCE];
};


#endif // GLESAPPCONTEXT_H
