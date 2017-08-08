#ifndef BULLET_H
#define BULLET_H
#include <glm/glm.hpp>
#include "visionnode.h"
#include "textureresource.h"
#include "IRenderable.h"
#include "shader.h"
#include "frameitem.h"
class Bullet: public FrameItem
{
public:
    Bullet(ShaderMap* map,  FrameItem* parent = 0);
    virtual ~Bullet(){}
    void setDir(const glm::vec3& dir);
    void setSpeed(float speeed);
    void setMaxDistance(float dist);
    void inline setSrcPos(const glm::vec3& pos){
        _posSrc = pos;
        setPosition(pos);
    }
    bool isDead();
    void updatePos(const float& elasped);
protected:
    void onDrawSelf(const Vision::FrameEvent&,const glm::mat4&);

private:
    Texture2dId         _texture;
    bool            _isDead;
    float           _attrSpeed;
    float           _attrMaxDistance;
    float           _attrPowerRadius;
    float           _attrHurt;
    glm::vec3       _dir;
    glm::vec3       _posSrc;

};

#endif // BULLET_H
