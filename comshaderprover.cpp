#include "comshaderprover.h"

COMShaderProver::COMShaderProver()
{
    mShaderInfo = NULL;
}
ShaderInfo* COMShaderProver::getShaderInfo(){
    if(!mShaderInfo){
        mShaderInfo = new ShaderInfo;
        mShaderInfo->setFsFileName("./common.fsh");
        mShaderInfo->setVsFileName("./common.vsh");
        mShaderInfo->addVertex("position");
        mShaderInfo->addUniform("pvmMat");
    }
    return mShaderInfo;
}
COMShaderProver::~COMShaderProver(){
    delete mShaderInfo;
}
