#ifndef MESH_H
#define MESH_H
#ifdef UBUNTU_WITH_GL
#include <GL/glew.h>
#include <GL/glut.h>
#endif
#ifdef WIN_WITH_OPENGL_ES2
typedef int GLint;
typedef unsigned int GLuint;
#include <gles2/gl2.h>
#endif
#include <QDebug>
#include "baserender.h"
#include "camera.h"
#include "transform.h"
#include "renderobserver.h"

class MeshAccessory;


class Mesh
{
public:
    enum AccessoryType{
        CAMERA_ACCESSORY,
        TRANSFORM_ACCESSORY,
        RENDER_ACCESSORY,
        NUM_ACCESSORYS
    };

    Mesh(BaseRender* render = NULL);
    int meshInit();
    void update();
    void onSurfaceChanaged(const GLsizei& width,const GLsizei& height);

    inline void roteXf(const GLfloat& angle){
        Transform *mTransform = (Transform *)mAccessorys[TRANSFORM_ACCESSORY];
        if(mTransform)
            mTransform->setRote(*mTransform->getRote()+glm::vec3(angle,0,0));
    }
    inline void roteYf(const GLfloat& angle){
        Transform *mTransform = (Transform *)mAccessorys[TRANSFORM_ACCESSORY];
        if(mTransform){
            mTransform->setRote(*mTransform->getRote()+glm::vec3(0,angle,0));
        }
    }
    inline void roteZf(const GLfloat& angle){
        Transform *mTransform = (Transform *)mAccessorys[TRANSFORM_ACCESSORY];
        if(mTransform){
            mTransform->setRote(*mTransform->getRote()+glm::vec3(0,0,angle));
        }
    }

    inline void transXf(const GLfloat& value){
        Transform *mTransform = (Transform *)mAccessorys[TRANSFORM_ACCESSORY];
        if(mTransform){
            mTransform->setPos(*mTransform->getPos()+glm::vec3(value,0,0));
        }
    }
    inline void transYf(const GLfloat& value){
        Transform *mTransform = (Transform *)mAccessorys[TRANSFORM_ACCESSORY];
        if(mTransform){
            mTransform->setPos(*mTransform->getPos()+glm::vec3(0,value,0));
        }
    }
    inline void transZf(const GLfloat& value){
        Transform *mTransform = (Transform *)mAccessorys[TRANSFORM_ACCESSORY];
        if(mTransform){
            mTransform->setPos(*mTransform->getPos()+glm::vec3(0,0,value));
        }
    }
    inline void scaleXf(const GLfloat& value){
        Transform *mTransform = (Transform *)mAccessorys[TRANSFORM_ACCESSORY];
        if(mTransform){
            mTransform->setScale(*mTransform->getScale()*glm::vec3(value,1.0f,1.0f));
        }
    }
    inline void scaleYf(const GLfloat& value){
        Transform *mTransform = (Transform *)mAccessorys[TRANSFORM_ACCESSORY];
        if(mTransform){
            mTransform->setScale(*mTransform->getScale()*glm::vec3(1.0f,value,1.0f));
        }
    }
    inline void scaleZf(const GLfloat& value){
        Transform *mTransform = (Transform *)mAccessorys[TRANSFORM_ACCESSORY];
        if(mTransform){
            mTransform->setScale(*mTransform->getScale()*glm::vec3(1.0f,1.0f,value));
        }
    }
    inline void setAccessory(MeshAccessory* accessory,AccessoryType type){
        mAccessorys[type] = accessory;
        accessory->setMesh(this);
    }

    inline const MeshAccessory* getMeshAccessory(AccessoryType type){
        return  mAccessorys[type];
    }


    virtual ~Mesh();
protected:
    inline float getRatio(){return mRatio;}
private:
    void setProjectionMatrix(const GLsizei& width,const GLsizei& height);
private:
    float  mRatio;
    RenderObServer *mObserver;
    MeshAccessory* mAccessorys[NUM_ACCESSORYS];
};

#endif // MESH_H
