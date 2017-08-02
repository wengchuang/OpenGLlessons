#include "glesappcontext.h"
#include "textureresource.h"
#include "glutimermanager.h"

GLESAppContext::GLESAppContext()
{
    int errCode = -1;
    Resources[TEXTURE_RESOURCE] = new TextureResource;
    assert(Resources[TEXTURE_RESOURCE] != NULL);
    errCode = Resources[TEXTURE_RESOURCE]->resourceInitialize();
    assert(errCode == 0);

    Resources[TIMERMANAGER_RESOURCE] = new GLUTimerManager;
    assert(Resources[TIMERMANAGER_RESOURCE]!=NULL);
    errCode = Resources[TIMERMANAGER_RESOURCE]->resourceInitialize();
    assert(errCode == 0);
}
GLESAppContext::~GLESAppContext(){
    for(int i=0;i<NUM_RESOURCE;i++){
        Resources[i]->resourceUnInitialize();
        delete Resources[i];
    }
}
