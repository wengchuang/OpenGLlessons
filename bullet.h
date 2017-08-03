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
    Bullet(ShaderMap* map);
protected:
    virtual void onRender(int width, int height, const glm::mat4 &pvMat);
private:
    Vision::VisionNode  bulletBody;
    Texture2dId         _texture;
            /// 是否死亡
    bool            _isDead;
    /// 速度
    float           _attrSpeed;
    /// 作用的最远距离
    float           _attrMaxDistance;
    /// 威力    半径
    float           _attrPowerRadius;
    /// 伤害值
    float           _attrHurt;
    /// 飞行方向
    glm::vec3       _dir;
    /// 初始化位置
    glm::vec3       _posSrc;
    ShaderMap*      mShaderMap;
};

#endif // BULLET_H
