#include "nitro/types.h"

extern unsigned int CaptureContextJointMtx();
extern unsigned int NNS_G3dRenderObjResetCallBack();
extern unsigned int NNS_G3dRenderObjSetCallBack();

void InstallActorJointMatrixCaptureCallback(int actor) {
  *(int *)(*(int *)(actor + 0x230) + 0x50) = actor;
  NNS_G3dRenderObjResetCallBack((void *)(*(int *)(actor + 0x230) + 0x24));
  NNS_G3dRenderObjSetCallBack(*(int *)(actor + 0x230) + 0x24,CaptureContextJointMtx,0,6,3);
}
