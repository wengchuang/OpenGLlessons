#include "mesh.h"
#include <string.h>
#include <QDebug>

Mesh::Mesh(BaseRender* render)
{
    mAccessorys[RENDER_ACCESSORY] = render;
    Camera* camera = new Camera;
    mAccessorys[CAMERA_ACCESSORY] = camera;
    Transform* transform = new Transform;
    mAccessorys[TRANSFORM_ACCESSORY] = transform;

    mObserver = new RenderObServer(transform,camera);
    render->setObserver(mObserver);
}
int Mesh::meshInit(){
    int ret = -1;
    qDebug()<<"meshInit...";

    for(int i=0;i<NUM_ACCESSORYS;i++){
        ret = mAccessorys[i]->init();
        if(ret < 0){
            return ret;
        }
    }
    qDebug()<<"meshInit end";
    return ret;
}

void Mesh::setProjectionMatrix(const GLsizei& width,const GLsizei& height){
    glViewport(0,0,width,height);
    mRatio = (float)width/(float)height;
    Camera*mCamera = (Camera*) mAccessorys[CAMERA_ACCESSORY];
    if(mCamera){

        mCamera->setProjection(60.0f,mRatio,3.0,1000.0f);
    }
}
void Mesh::onSurfaceChanaged(const GLsizei& width,const GLsizei& height){
    setProjectionMatrix(width,height);
    BaseRender* mRender = (BaseRender*)mAccessorys[RENDER_ACCESSORY];
    if(mRender){
        mRender->onSurfaceChanaged(width,height);
    }
}


void Mesh::update(){
    BaseRender* mRender = (BaseRender*)mAccessorys[RENDER_ACCESSORY];
    if(mRender){
        glClear(GL_COLOR_BUFFER_BIT);

        //Camera*mCamera = (Camera*) mAccessorys[CAMERA_ACCESSORY];
        //Transform*mTransform = (Transform*)mAccessorys[TRANSFORM_ACCESSORY];
        mRender->update();
    }
}
Mesh::~Mesh(){
    delete mObserver;
    delete mAccessorys[CAMERA_ACCESSORY];
    delete mAccessorys[TRANSFORM_ACCESSORY];
    qDebug()<<"~Mesh()";
}
