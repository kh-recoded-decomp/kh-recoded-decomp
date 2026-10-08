#include "nitro/types.h"

typedef struct ModelActor {
    u8 kind;
    u8 pad_001[0x18f];
    u8 renderObj[1];
} ModelActor;

extern void NNS_G3dRenderObjResetCallBack(void *renderObj);
extern void NNS_G3dRenderObjSetCallBack(
    void *renderObj, void (*callback)(void *), u8 *address, u8 command, int timing);
extern void ModelRenderCallbackKindFF(void *renderState);
extern void ModelRenderCallbackKindFD(void *renderState);
extern void ModelRenderCallbackKind12(void *renderState);
extern void ModelRenderCallbackKindC(void *renderState);

void InstallModelRenderCallback(ModelActor *actor)
{
    switch (actor->kind) {
    case 0xff:
        NNS_G3dRenderObjResetCallBack(actor->renderObj);
        NNS_G3dRenderObjSetCallBack(actor->renderObj, ModelRenderCallbackKindFF, NULL, 6, 3);
        break;
    case 0xfd:
        NNS_G3dRenderObjResetCallBack(actor->renderObj);
        NNS_G3dRenderObjSetCallBack(actor->renderObj, ModelRenderCallbackKindFD, NULL, 6, 3);
        break;
    case 0x12:
    case 0x16:
    case 0x17:
        NNS_G3dRenderObjResetCallBack(actor->renderObj);
        NNS_G3dRenderObjSetCallBack(actor->renderObj, ModelRenderCallbackKind12, NULL, 6, 3);
        break;
    case 0x0c:
    case 0xfe:
        NNS_G3dRenderObjResetCallBack(actor->renderObj);
        NNS_G3dRenderObjSetCallBack(actor->renderObj, ModelRenderCallbackKindC, NULL, 6, 3);
        break;
    }
}
