#ifndef CAMERA_H
#define CAMERA_H
#include <glm/gtx/transform.hpp>
#include <glm/glm.hpp>
class Camera
{
public:
    Camera();
    inline glm::mat4 getViewProjection()const{
        /*Projection * View*/
        return projection*glm::lookAt(pos,forword,up);
    }
    void setProjection(const float& fovAngle,
                       const float& aspect,const float& zNear,const float& zFar);
private:
    glm::mat4  projection;
    glm::vec3  pos;
    glm::vec3  forword;
    glm::vec3  up;
};

#endif // CAMERA_H
