#ifndef GLESAPPCONTEXT_H
#define GLESAPPCONTEXT_H
class IResourceItem;
#include "itimermanager.h"
#include "textureresource.h"

class GLESAppContext
{
public:
    enum RESOURCETYPE{
        TEXTURE_RESOURCE,
        TIMERMANAGER_RESOURCE,
        NUM_RESOURCE
    };
    ~GLESAppContext();
public:
    inline TextureResource* getTextureResource(){
        return (TextureResource*)Resources[TEXTURE_RESOURCE];
    }
    inline ITimerManager* getTimerManagerResource(){
        return (ITimerManager*)Resources[TIMERMANAGER_RESOURCE];
    }
private:
    friend class AbsGLES2App;
    GLESAppContext();

private:
    IResourceItem* Resources[NUM_RESOURCE];
};


#endif // GLESAPPCONTEXT_H
