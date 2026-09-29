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

typedef struct ActorEffect {
    u8 data[0x230];
} ActorEffect;

typedef struct Actor Actor;
typedef void (*ActorSetHeadingFunc)(Actor *actor, s16 heading);

struct Actor {
    u8 pad_0000[0x210];
    ActorSetHeadingFunc setHeading;
    u8 pad_0214[0x230 - 0x214];
    ActorModel *model;
    u8 pad_0234[0x930 - 0x234];
    u8 playerIndex;
    u8 pad_0931[0x9d4 - 0x931];
    ActorEffect effects[2];
    u8 pad_0E34[0xec4 - 0xe34];
    u8 unk_0EC4[0x16f0 - 0xec4];
    u8 attachState[0x10];
};

extern void func_01ffb12c(ModelInstance *instance);
extern void func_ov059_020c9048(Actor *actor, void *attachState);
extern void func_ov021_020a9af0(ActorEffect *effect);
extern void func_ov021_020aafd4(void *object);
extern s16 func_ov059_020cd0e4(Actor *actor);
extern void func_ov021_020a8b44(u8 playerIndex);
extern void func_ov059_020c7ee4(Actor *actor);

void Actor_Draw_020cbde0(Actor *actor)
{
    s16 heading;
    int i;

    actor->model->instance.renderObj.flag |= NNS_G3D_RENDEROBJ_FLAG_RECORD;
    if ((actor->model->flags & 0x20) == 0) {
        func_01ffb12c(&actor->model->instance);
    }
    actor->model->instance.renderObj.flag &= ~NNS_G3D_RENDEROBJ_FLAG_RECORD;
    func_ov059_020c9048(actor, actor->attachState);
    for (i = 0; i < 2; i++) {
        func_ov021_020a9af0(&actor->effects[i]);
    }
    func_ov021_020aafd4(actor->unk_0EC4);
    heading = func_ov059_020cd0e4(actor);
    if (actor->setHeading != NULL) {
        actor->setHeading(actor, 0);
    }
    func_ov021_020a8b44(actor->playerIndex);
    if (actor->setHeading != NULL) {
        actor->setHeading(actor, heading);
    }
    func_ov059_020c7ee4(actor);
}
