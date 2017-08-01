#include "comshaderprover.h"
template<typename T, size_t N>
char(&ArraySizeHelper(const T(&array)[N]))[N];
#define ARRAY_SIZE(array) (sizeof(ArraySizeHelper(array)))

static ShaderInfo info={"./common.vsh","./common.fsh"};
static VertexLocDesc vertexLoc[]={
    {0,"position"},{1,"_uv"}
};
static UniformLocDesc uniformDesc[]={
    {"pvmMat",UniformLocDesc::TYPE_FOR_PVM},
    {"_texture",UniformLocDesc::TYPE_FOR_NORMAL}
};
COMShaderProver::COMShaderProver()
{
    int i = 0;
    for(i=0;i<ARRAY_SIZE(vertexLoc);i++){
        info.vertexDescs[i] = &vertexLoc[i];
    }
    info.vertexDescs[i] = NULL;

    for(i = 0;i<ARRAY_SIZE(uniformDesc);i++){
        info.uniformDescs[i] = &uniformDesc[i];
    }
    info.uniformDescs[i] = NULL;
}
ShaderInfo* COMShaderProver::getShaderInfo(){
    return &info;
}
