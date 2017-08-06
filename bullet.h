#ifndef BULLET_H
#define BULLET_H
#include <glm/glm.hpp>
#include "visionnode.h"
#include "textureresource.h"
#include "IRenderable.h"
#include "shader.h"
class Bullet:public Vision::IModelRenderable
{
public:
    Bullet(ShaderMap* map);
    virtual ~Bullet(){}
    void setDir(const glm::vec3& dir);
    void setSize(const glm::vec2& Size);
    void setSpeed(float speeed);
    void setMaxDistance(float dist);
    void setPosition(const glm::vec3& pos);
    bool isDead();

    virtual void onRender(const Vision::FrameEvent&,const glm::mat4&);
private:
    void update(const float& elasped);
private:
    Vision::VisionNode  bulletBody;
    Texture2dId         _texture;
    bool            _isDead;
    float           _attrSpeed;
    float           _attrMaxDistance;
    float           _attrPowerRadius;
    float           _attrHurt;
    glm::vec3       _dir;
    glm::vec3       _posSrc;
    ShaderMap*      mShaderMap;

};

#endif // BULLET_H
