#include "nitro/types.h"

struct NNSG3dRS_;
typedef void (*SbcCallback)(struct NNSG3dRS_ *);

typedef struct RenderObj {
    u8 pad_00[0x2c];
    void *userData;
} RenderObj;

typedef struct SceneObject {
    u8 pad_00[0x24];
    RenderObj renderObj;
} SceneObject;

typedef struct ActorBody {
    SceneObject *object;
} ActorBody;

typedef struct Actor {
    u8 pad_000[0xd18];
    ActorBody *body;
    u8 pad_d1c[0xf00 - 0xd1c];
    int useAltCallback;
} Actor;

extern void ClearSbcCallback_020188b8(RenderObj *renderObj);
extern void RegisterSbcCallback_020188a4(RenderObj *renderObj, SbcCallback callback, u8 *unused, u8 cmd, int timing);
extern void func_ov001_020897d0(struct NNSG3dRS_ *rs);
extern void func_0202f5bc(struct NNSG3dRS_ *rs);

void Actor_InstallModelCallback_02089898(Actor *actor)
{
    RenderObj *renderObj = &actor->body->object->renderObj;

    ClearSbcCallback_020188b8(renderObj);
    if (actor->useAltCallback == 0) {
        RegisterSbcCallback_020188a4(renderObj, func_ov001_020897d0, NULL, 6, 3);
        return;
    }
    RegisterSbcCallback_020188a4(renderObj, func_0202f5bc, NULL, 6, 3);
}
