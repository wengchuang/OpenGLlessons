#include "renderobserver.h"

RenderObServer::RenderObServer(Transform*transform,Camera*camera)
{
    mTransform = transform;
    mCamera    = camera;
}
glm::mat4 RenderObServer::observerViewMatrix(){
    return mCamera->getViewProjection();
}
glm::mat4 RenderObServer::observerModelMatrix(){
    return mTransform->getModelMatrix();
}
RenderObServer::~RenderObServer(){

}


