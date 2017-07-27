#ifndef TRANSFORM_H
#define TRANSFORM_H
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include "meshaccessory.h"
class Transform : public MeshAccessory
{
public:
    Transform(const glm::vec3& pos=glm::vec3(),
              const glm::vec3& rot=glm::vec3(),
              const glm::vec3& scale=glm::vec3(1.0f,1.0f,1.0f)){
        this->pos = pos;
        this->rot = rot;
        this->scale = scale;

    }
    inline void setPos(const glm::vec3& pos){
        this->pos = pos;
    }
    inline void setScale(const glm::vec3& scale){
        this->scale = scale;
    }
    inline void setRote(const glm::vec3& rot){
        this->rot = rot;
    }
    inline glm::vec3* getPos(){
        return &pos;
    }
    inline glm::vec3* getScale(){
        return &scale;
    }
    inline glm::vec3* getRote(){
        return &rot;
    }
    inline glm::mat4 getModelMatrix()const{
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model,pos);
        model = glm::rotate(model,glm::radians(rot.x),glm::vec3(1.0f,0.0f,0.0f));
        model = glm::rotate(model,glm::radians(rot.y),glm::vec3(0.0f,1.0f,0.0f));
        model = glm::rotate(model,glm::radians(rot.z),glm::vec3(0.0f,0.0f,1.0f));
        model = glm::scale(model,scale);
        return model;
    }
private:
    glm::vec3 pos;
    glm::vec3 rot;
    glm::vec3 scale;
};

#endif // TRANSFORM_H
