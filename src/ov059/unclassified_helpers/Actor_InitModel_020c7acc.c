#pragma opt_rotateloops off
#pragma opt_common_subs off
#pragma opt_propagation off
#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "nnsys/g3d.h"

typedef struct ShapeParams {
    u32 flags;
    fx32 extentA;
    fx32 extentB;
    fx32 extentC;
    fx32 extentD;
} ShapeParams;

typedef struct LinkTarget {
    u8 kind;
    u8 group;
} LinkTarget;

typedef struct ModelInstance {
    u8 pad_00[0x20];
    NNSG3dRenderObj renderObj;
} ModelInstance;

typedef struct ActorModel {
    u32 flags;
    ModelInstance instance;
    u8 pad_78[4];
    NNSG3dResMdl *polygonModel;
} ActorModel;

typedef struct ModelHolder {
    ActorModel *model;
    u8 pad_04[0x36];
    u16 frame;
} ModelHolder;

typedef struct MotionSlot {
    int active;
    u8 pad_04[0x28];
} MotionSlot;

typedef struct Actor {
    u8 pad_000[4];
    u8 entry[0x22c];
    ModelHolder holder;
    u8 pad_26c[0x694 - 0x26c];
    u8 shadow[0x6b8 - 0x694];
    void *jointResults;
    int nodeIndices[4];
    u8 pad_6cc[0x75c - 0x6cc];
    int targetIndex;
    u8 pad_760[4];
    int motionCount;
    int motionTimer;
    MotionSlot motions[3];
    u8 animModel[0x930 - 0x7f0];
    u8 slot;
    u8 pad_931[0xb];
    int nameIndex;
} Actor;

extern const char *data_0205615c[];
extern const char data_ov059_020cff28[];
extern const char data_ov059_020cff3c[];
extern const char data_ov059_020cff50[];
extern const NNSG3dResName data_ov059_020cfe40;
extern const NNSG3dResName data_ov059_020cfe50;
extern const NNSG3dResName data_ov059_020cfe30;
extern const NNSG3dResName data_ov059_020cfe20;
extern VecFx32 data_02053438;

extern int OS_SPrintf_02002428(char *dst, const char *fmt, ...);
extern void ActorEntry_Init_020357d8(int slot, void *entry, u16 group, const LinkTarget *link, const ShapeParams *shape, BOOL flag20, s8 priority);
extern void func_02036a70(int index, u32 value);
extern void ActorSlot_SetField1CCByIndex_02036a98(int index, u32 value);
extern void *RetainOrInitializeSharedRecord_0202c80c(int name, int context);
extern void *func_0202c48c(u32 name, u32 heap);
extern void func_020358b0(int index, void *record, void *block, int context);
extern void NNSi_FndFreeFromDefaultHeap_0202a1c4(void *block);
extern void *func_02036240(int index);
extern void func_02038a90(ModelHolder *holder, void *actor);
extern void selectJointAnimationBlend_0202f2cc(void *state, u16 track, void *table, s16 blend);
extern void Model_SetAllPolygonIds_0201a8c0(NNSG3dResMdl *mdl, int polygonId);
extern BOOL ShadowVolume_Init_02036b44(void *shadow, const VecFx32 *position, fx32 scale, NNSG3dResMdl *model);
extern void func_0202f5b4(void *instance, int color);
extern void func_0202f590(void *instance, int flag);
extern void ActorSlot_SetFlag8ByIndex_02036120(int index, BOOL enable);
extern int FindResourceIndexByName_0201aafc(const NNSG3dResDict *dict, const NNSG3dResName *name);
extern void *NNSi_FndAllocFromDefaultHeap_0202a178(u32 size);
extern void Actor_InitNodeCaptureCallback_020cd254(Actor *actor);
extern void InitAnimatedModel_020ac864(void *model, char *source, int slot);

static inline NNSG3dRenderObj *GetRenderObj(ActorModel *model)
{
    return &model->instance.renderObj;
}

static inline void SetJntAnmBuffer(NNSG3dRenderObj *obj, void *buffer)
{
    obj->recJntAnm = buffer;
}

static inline int FindNodeIndex(NNSG3dRenderObj *obj, const NNSG3dResName *name)
{
    NNSG3dResNodeInfo *info;
    int index;
    if (obj->resMdl != NULL) {
        info = &obj->resMdl->nodeInfo;
    } else {
        info = NULL;
    }
    if (info != NULL) {
        index = FindResourceIndexByName_0201aafc(&info->dict, name);
    } else {
        index = -1;
    }
    return index;
}

static inline void ResetMotions(Actor *actor)
{
    int i;
    for (i = 0; i < 3; i++) {
        actor->motions[i].active = 0;
    }
}

static inline void InitEntry(Actor *actor, LinkTarget *link, ShapeParams *shape)
{
    ActorEntry_Init_020357d8(actor->slot, actor->entry, 1 << actor->slot, link, shape, 0, 0);
}

void Actor_InitModel_020c7acc(Actor *actor)
{
    u8 slot;
    LinkTarget link;
    ShapeParams shape;
    void *record;
    void *block;
    ActorModel *model;
    int context;
    char name[0x81];
    char animName[0x7f];
    ModelHolder *holder;

    slot = actor->slot;
    shape.extentB = 0x900;
    shape.flags = 1;
    shape.extentA = 0xf00;
    context = slot + 8;
    link.kind = 0;
    link.group = slot;
    InitEntry(actor, &link, &shape);
    func_02036a70(actor->slot, 0);
    ActorSlot_SetField1CCByIndex_02036a98(actor->slot, 0);
    OS_SPrintf_02002428(name, data_ov059_020cff28, data_0205615c[actor->nameIndex], 0);
    record = RetainOrInitializeSharedRecord_0202c80c((int)name, context);
    OS_SPrintf_02002428(name, data_ov059_020cff3c, data_0205615c[actor->nameIndex], 0);
    block = func_0202c48c((u32)name, 0x11);
    func_020358b0(actor->slot, record, block, context);
    NNSi_FndFreeFromDefaultHeap_0202a1c4(block);
    func_02038a90(&actor->holder, func_02036240(actor->slot));
    holder = &actor->holder;
    holder->frame = 0;
    model = holder->model;
    if (!(model->flags & 0x20)) {
        selectJointAnimationBlend_0202f2cc(&model->instance, 3, (u8 *)&model->instance + 0xd8, 0);
    }
    Model_SetAllPolygonIds_0201a8c0(actor->holder.model->polygonModel, 0x3f);
    ShadowVolume_Init_02036b44(actor->shadow, &data_02053438, 0x119a, NULL);
    func_0202f5b4(&actor->holder.model->instance, 0x7fff);
    func_0202f590(&actor->holder.model->instance, 1);
    actor->holder.model->flags |= 0x40;
    ActorSlot_SetFlag8ByIndex_02036120(actor->slot, 0);
    if (actor->nodeIndices[0] != -2) {
        actor->nodeIndices[0] = FindNodeIndex(GetRenderObj(actor->holder.model), &data_ov059_020cfe40);
    }
    if (actor->nodeIndices[1] != -2) {
        actor->nodeIndices[1] = FindNodeIndex(GetRenderObj(actor->holder.model), &data_ov059_020cfe50);
    }
    if (actor->nodeIndices[2] != -2) {
        actor->nodeIndices[2] = FindNodeIndex(GetRenderObj(actor->holder.model), &data_ov059_020cfe30);
    }
    if (actor->nodeIndices[3] != -2) {
        actor->nodeIndices[3] = FindNodeIndex(GetRenderObj(actor->holder.model), &data_ov059_020cfe20);
    }
    actor->jointResults = NNSi_FndAllocFromDefaultHeap_0202a178(actor->holder.model->instance.renderObj.resMdl->info.numNode * 0x58);
    SetJntAnmBuffer(GetRenderObj(actor->holder.model), actor->jointResults);
    Actor_InitNodeCaptureCallback_020cd254(actor);
    OS_SPrintf_02002428(animName, data_ov059_020cff50, data_0205615c[actor->nameIndex]);
    InitAnimatedModel_020ac864(actor->animModel, animName, actor->slot);
    ResetMotions(actor);
    actor->motionCount = 0;
    actor->targetIndex = -1;
    actor->motionTimer = 0;
}
