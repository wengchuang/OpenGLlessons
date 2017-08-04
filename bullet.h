#ifndef BULLET_H
#define BULLET_H
#include <glm/glm.hpp>
#include "visionnode.h"
#include "textureresource.h"
#include "IRenderable.h"
#include "shader.h"
class Bullet:public IModelRenderable
{
public:
    Bullet(ShaderMap* map,const unsigned long& timeSpec,const int& curTime);
    virtual ~Bullet(){}
    void setDir(const glm::vec3& dir);
    void setSize(const glm::vec2& Size);
    void setSpeed(float speeed);
    void setMaxDistance(float dist);
    void setPosition(const glm::vec3& pos);
    inline void setTimes(const int& curTime){
        this->curTime = curTime;
        update();
    }
    bool isDead();

    virtual void onRender(int width, int height, const glm::mat4 &pvMat);
private:
    void update();
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
    unsigned long   timeSpec;
    int             beginTimes;
    int             curTime;
};

#endif // BULLET_H
