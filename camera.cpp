#include "camera.h"
#include <GL/glew.h>
Camera::Camera(){
    this->pos = glm::vec3(0,0,5.0f);
    this->forword = glm::vec3(0.0f,.0f,0.0f);
    this->up = glm::vec3(0.0f,1.0f,0.0f);
    setProjection(60.0f,
                  ((float)4.0/3),
                   3.f,7.0f);
}
void Camera::setProjection(const float& fovAngle,
                   const float& aspect,const float& zNear,const float& zFar){
    this->projection =glm::perspective(glm::radians(fovAngle),
                                       aspect,zNear,zFar);

}
