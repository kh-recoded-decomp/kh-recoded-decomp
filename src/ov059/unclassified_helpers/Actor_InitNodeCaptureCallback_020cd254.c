#include "nitro/types.h"
#include "nnsys/g3d.h"

typedef struct ModelInstance {
    u16 dirtyFlags;
    u8 pad_02[0x1e];
    NNSG3dRenderObj renderObj;
} ModelInstance;

typedef struct ActorModel {
    u32 flags;
    ModelInstance instance;
} ActorModel;

typedef struct Actor {
    u8 pad_000[0x230];
    ActorModel *model;
} Actor;

extern void ClearSbcCallback_020188b8(NNSG3dRenderObj *renderObj);
extern void RegisterSbcCallback_020188a4(NNSG3dRenderObj *renderObj, NNSG3dSbcCallBackFunc func,
                                         u8 *sbc, u8 cmd, NNSG3dSbcCallBackTiming timing);
extern void func_ov059_020c9134(struct NNSG3dRS_ *renderState);

void Actor_InitNodeCaptureCallback_020cd254(Actor *actor)
{
    actor->model->instance.renderObj.ptrUser = actor;
    ClearSbcCallback_020188b8(&actor->model->instance.renderObj);
    RegisterSbcCallback_020188a4(&actor->model->instance.renderObj, func_ov059_020c9134, NULL, 6,
                                 NNS_G3D_SBC_CALLBACK_TIMING_C);
}
