#pragma opt_lifetimes off
#pragma opt_common_subs off
#pragma opt_rotateloops off
#pragma opt_propagation off
#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u32 flags;
    fx32 extentA;
    fx32 extentB;
    fx32 extentC;
    fx32 extentD;
} ShapeParams;

typedef struct {
    u8 pad_00[0x17];
    u8 materialCount;
    u8 pad_18[0x40 - 0x18];
    u8 dictionary[4];
} ModelResource;

typedef struct {
    u8 pad_00[4];
    ModelResource *resource;
    u8 pad_08[0x34 - 0x08];
    void *materialWork;
} RenderObject;

typedef struct {
    u8 pad_00[0x20];
    RenderObject render;
    u8 pad_58[0x78 - 0x58];
    void *renderModel;
    u8 pad_7c[0xd8 - 0x7c];
    u8 blendTable[4];
} ModelAnimation;

typedef struct {
    u32 flags;
    ModelAnimation animation;
} PlayerModel;

typedef struct {
    VecFx32 offset;
    ShapeParams shape;
} SpawnShape;

typedef struct {
    PlayerModel *model;
    u8 pad_04[0x3a - 0x04];
    s16 frame;
} ModelLink;

typedef struct {
    int state;
    u8 pad_04[0x2c - 0x04];
} ActionSlot;

typedef struct {
    u8 pad_000[4];
    u8 entry[0x230 - 0x004];
    ModelLink link;
    u8 pad_26c[0x694 - 0x26c];
    u8 shadow[0x6b8 - 0x694];
    void *materialWork;
    int jointIds[4];
    u8 pad_6cc[0x75c - 0x6cc];
    int linkMode;
    u8 pad_760[0x764 - 0x760];
    int linkTimer;
    int linked;
    ActionSlot slots[6];
    u8 pad_874[0x874 - 0x874];
    u8 animModel[0x9b4 - 0x874];
    u8 player;
    u8 pad_9b5[0x9b8 - 0x9b5];
    int character;
    u8 pad_9bc[0xa0c - 0x9bc];
    fx32 radius;
} PlayerActor;

typedef struct {
    const char *names[4];
} JointNameTable;

extern const VecFx32 data_ov052_020d20d0;
extern const char *data_0205615c[];
extern const char data_ov052_020d217c[];
extern const char data_ov052_020d2190[];
extern const char data_ov052_020d21a4[];
extern const char data_ov052_020d21a8[];
extern const JointNameTable data_ov052_020d216c;
extern char data_ov052_020d21c0[];
extern const VecFx32 data_02053438;

extern void ActorEntry_Init_020357d8(int slot, void *entry, u16 group, const u8 *attributes, const ShapeParams *shape, BOOL flag20, s8 priority);
extern void func_02036a70(int player, int value);
extern void ActorSlot_SetField1CCByIndex_02036a98(int player, int value);
extern int OS_SPrintf_02002428(char *dst, const char *fmt, ...);
extern void *RetainOrInitializeSharedRecord_0202c80c(char *name, int slot);
extern void *func_0202c48c(char *name, int mode);
extern void func_020358b0(int player, void *record, void *block, int slot);
extern void NNSi_FndFreeFromDefaultHeap_0202a1c4(void *block);
extern void *NNSi_FndAllocFromDefaultHeap_0202a178(u32 size);
extern void *func_02036240(int player);
extern void func_02038a90(ModelLink *link, void *source);
extern void selectJointAnimationBlend_0202f2cc(void *animation, u16 track, void *blendTable, s16 blendIndex);
extern void Model_SetAllPolygonIds_0201a8c0(void *model, int id);
extern BOOL ShadowVolume_Init_02036b44(void *shadow, const VecFx32 *position, fx32 scale, void *model);
extern void func_0202f5b4(void *animation, int value);
extern void func_0202f590(void *animation, int value);
extern void ActorSlot_SetFlag8ByIndex_02036120(int player, int value);
extern void func_01ff86fc(int value, void *dst, u32 size);
extern int FindResourceIndexByName_0201aafc(void *dictionary, const char *name);
extern void func_ov052_020d071c(PlayerActor *actor);

static inline void SetEntryAttributes(u8 *attributes, u8 player)
{
    attributes[0] = 0;
    attributes[1] = player;
}

static inline void SelectDefaultBlend(ModelAnimation *animation)
{
    selectJointAnimationBlend_0202f2cc(animation, 3, animation->blendTable, 0);
}

static inline void SetMaterialWork(RenderObject *render, void *work)
{
    render->materialWork = work;
}
extern void InitAnimatedModel_020ac864(void *model, char *source, int slot);

void InitPlayerActorModel_020c7460(PlayerActor *actor)
{
    char fileName[0x81];
    char modelName[0x7f];
    SpawnShape spawn;
    JointNameTable jointNames;
    u8 attributes[2];
    u8 player;
    ModelLink *link;
    int slot;
    void *record;
    void *block;
    int i;
    void *dictionary;
    int jointId;

    player = actor->player;
    slot = player + 8;
    spawn.offset = data_ov052_020d20d0;
    spawn.shape.flags = 1;
    actor->radius = 0x1800;
    spawn.shape.extentB = 0x900;
    spawn.shape.extentA = actor->radius - 0x900;
    SetEntryAttributes(attributes, player);
    ActorEntry_Init_020357d8(actor->player, actor->entry, 1 << actor->player, attributes, &spawn.shape, 0, 0);
    func_02036a70(actor->player, 0);
    ActorSlot_SetField1CCByIndex_02036a98(actor->player, 0);
    OS_SPrintf_02002428(fileName, data_ov052_020d217c, data_0205615c[actor->character], 0);
    record = RetainOrInitializeSharedRecord_0202c80c(fileName, slot);
    OS_SPrintf_02002428(fileName, data_ov052_020d2190, data_0205615c[actor->character], 0);
    block = func_0202c48c(fileName, 0x11);
    func_020358b0(actor->player, record, block, slot);
    NNSi_FndFreeFromDefaultHeap_0202a1c4(block);
    func_02038a90(&actor->link, func_02036240(actor->player));
    link = &actor->link;
    link->frame = 0;
    if (!(link->model->flags & 0x20)) {
        SelectDefaultBlend(&link->model->animation);
    }
    Model_SetAllPolygonIds_0201a8c0(actor->link.model->animation.renderModel, 0x3f);
    ShadowVolume_Init_02036b44(actor->shadow, &data_02053438, 0x119a, NULL);
    func_0202f5b4(&actor->link.model->animation, 0x7fff);
    func_0202f590(&actor->link.model->animation, 1);
    actor->link.model->flags |= 0x40;
    ActorSlot_SetFlag8ByIndex_02036120(actor->player, 0);
    jointNames = data_ov052_020d216c;
    for (i = 0; i < 4; i++) {
        if (actor->jointIds[i] != -2) {
            func_01ff86fc(0, data_ov052_020d21c0, 0x10);
            OS_SPrintf_02002428(data_ov052_020d21c0, data_ov052_020d21a4, jointNames.names[i]);
            if (actor->link.model->animation.render.resource != NULL) {
                dictionary = actor->link.model->animation.render.resource->dictionary;
            } else {
                dictionary = NULL;
            }
            if (dictionary != NULL) {
                jointId = FindResourceIndexByName_0201aafc(dictionary, data_ov052_020d21c0);
            } else {
                jointId = -1;
            }
            actor->jointIds[i] = jointId;
        }
    }
    actor->materialWork = NNSi_FndAllocFromDefaultHeap_0202a178(actor->link.model->animation.render.resource->materialCount * 0x58);
    SetMaterialWork(&actor->link.model->animation.render, actor->materialWork);
    func_ov052_020d071c(actor);
    OS_SPrintf_02002428(modelName, data_ov052_020d21a8, data_0205615c[actor->character]);
    InitAnimatedModel_020ac864(actor->animModel, modelName, actor->player);
    for (i = 0; i < 6; i++) {
        actor->slots[i].state = 0;
    }
    actor->linkTimer = 0;
    actor->linkMode = -1;
    actor->linked = 0;
}
