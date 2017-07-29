#ifndef IRENDEROBSERVER_H
#define IRENDEROBSERVER_H
#include <glm/glm.hpp>
class IRenderObserver{
public:
    virtual glm::mat4 observerViewMatrix() = 0;
    virtual glm::mat4 observerModelMatrix() = 0;
};
#endif // IRENDEROBSERVER_H
