#ifndef VISIONNODE_H
#define VISIONNODE_H
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include "visionmath.hpp"
namespace Vision{
    class VisionNode
    {
    public:
        VisionNode(void* user=0);
        void setSize(const glm::vec2& size);
        void update();

        glm::vec2  getSize() const
        {
            return  mSize;
        }
        ~VisionNode(){}
        inline void setPosition(const glm::vec3& pos)
        {
            this->pos    =   pos;
            bNeedUpdate  =  true;
        }
        inline const glm::vec3& getPosition() const
        {
            return  this->pos;
        }
        inline void setScale(const glm::vec3& scale)
       {
           this->scale  =   scale;
           bNeedUpdate  =  true;
       }
        inline const glm::vec3&    getScale() const
        {
            return  this->scale;
        }
        inline void  setRoteX(const float& angle)
        {
            rote.x += angle;
            bNeedUpdate  =  true;
        }
        inline void  setRoteY(const float& angle)
        {
            rote.y += angle;
            bNeedUpdate  =  true;
        }
        inline void  setRoteZ(const float& angle)
        {
            rote.z += angle;
            bNeedUpdate  =  true;
        }
        inline const glm::mat4&  getMatrix() const
        {
            return  local;
        }
        inline bool containPoint(glm::vec2& point){
            glm::vec3 minPos = -glm::vec3(mSize.x*0.5f,mSize.y*0.5f,0.0f) + pos;
            glm::vec3 maxPos = glm::vec3(mSize.x*0.5f,mSize.y*0.5f,0.0f) + pos;
            return ((point.x >= minPos.x) &&
                    (point.y >= minPos.y) &&
                    (point.x <= maxPos.x) &&
                    (point.y <= maxPos.y));
        }
    private:
        glm::vec3               pos;
        glm::vec3               rote;
        glm::vec3               scale;
        glm::vec2               mSize;
        glm::mat4               local;
        AxisAlignedBox<float>   alBox;
        bool                    bNeedUpdate;
    private:
        inline glm::mat4 getModelMatrix()const{
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model,pos);
            model = glm::rotate(model,glm::radians(rote.x),glm::vec3(1.0f,0.0f,0.0f));
            model = glm::rotate(model,glm::radians(rote.y),glm::vec3(0.0f,1.0f,0.0f));
            model = glm::rotate(model,glm::radians(rote.z),glm::vec3(0.0f,0.0f,1.0f));
            model = glm::scale(model,scale);
            return model;
        }
    };
}
#endif // VISIONNODE_H
