#ifndef MESHACCESSORY_H
#define MESHACCESSORY_H
#include <QtGlobal>
class Mesh;

class MeshAccessory
{
public:
    MeshAccessory();
    Mesh*getMesh(){
        return mesh;
    }
    void setMesh(Mesh* mesh){
        this->mesh = mesh;
    }
private:
    Mesh* mesh;
};

#endif // MESHACCESSORY_H
