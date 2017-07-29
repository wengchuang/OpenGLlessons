#ifndef RENDEROBSERVER_H
#define RENDEROBSERVER_H
#include "irenderobserver.h"
#include "transform.h"
#include "camera.h"

class RenderObServer : public IRenderObserver
{
public:
    RenderObServer(Transform*mTransform,Camera*mCamera);
    virtual glm::mat4 observerViewMatrix();
    virtual glm::mat4 observerModelMatrix();
    ~RenderObServer();
private:
    Transform*   mTransform;
    Camera*      mCamera;
};

#endif // RENDEROBSERVER_H
