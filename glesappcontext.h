#ifndef GLESAPPCONTEXT_H
#define GLESAPPCONTEXT_H
class IResourceItem;
#include "timermanager.h"
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
    inline Vision::TimerManager* getTimerManagerResource(){
        return (Vision::TimerManager*)Resources[TIMERMANAGER_RESOURCE];
    }
private:
    friend class AbsGLES2App;
    GLESAppContext();

private:
    IResourceItem* Resources[NUM_RESOURCE];
};


#endif // GLESAPPCONTEXT_H
