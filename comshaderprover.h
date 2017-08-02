#ifndef COMSHADERPROVER_H
#define COMSHADERPROVER_H
#include "shader.h"

class COMShaderProver
{
public:
    COMShaderProver();
    ShaderInfo* getShaderInfo();
    ~COMShaderProver();
private:
    ShaderInfo* mShaderInfo;
};

#endif // COMSHADERPROVER_H
