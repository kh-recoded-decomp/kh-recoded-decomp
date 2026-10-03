#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct SceneNode {
    u8 pad_00[0x74];
    s32 loaded;
    u8 pad_78[0x38];
    VecFx32 scale;
    u8 pad_bc[0x48];
} SceneNode;

typedef struct ObjectDef {
    u8 pad_000[0x59];
    u8 modelKind;
    u8 pad_05a[6];
    SceneNode nodes[4];
    s16 effectBank;
} ObjectDef;

typedef struct EntryGroupDesc {
    const void *data;
    s32 unk_04;
    s32 unk_08;
    s32 unk_0c;
    s32 unk_10;
} EntryGroupDesc;

typedef struct CollisionShape {
    u8 *data;
    s32 bounds[6];
    s32 kind;
} CollisionShape;

typedef void (*ComputeBoundsFunc)(CollisionShape *shape, s32 *bounds);

typedef struct HitCallback {
    void *func;
    void *context;
} HitCallback;

typedef struct Actor {
    u32 flags;
    u16 drawFlags;
    u8 pad_06[0x7a];
    u16 unk_80;
    u8 pad_82[0x32];
    VecFx32 scale;
    u8 pad_c0[0x4c];
    u8 collision[0xd];
    u8 falling;
    u8 pad_11a[0x16];
    CollisionShape shape;
    VecFx32 delta;
    s32 sweptBounds[6];
    u8 pad_174[0x10];
    HitCallback hitHandlers[2];
} Actor;

typedef struct FieldObject {
    u8 pad_00[4];
    ObjectDef *def;
    void *model;
    u8 pad_0c[0x24];
    u16 renderFlags;
    u8 actorId;
    u8 paletteId;
    u8 pad_34[4];
    VecFx32 position;
    u8 pad_44[3];
    s8 animIndex;
    void *resource;
    u8 pad_4c[4];
    u16 flags;
    s8 state;
    u8 pad_53[0x4d];
    s32 kind;
} FieldObject;

extern const u8 data_ov018_020a3850[];
extern const VecFx32 data_02053438;
extern ComputeBoundsFunc data_020559c0[];

extern void ZeroBytes0x14_020a8adc(void *obj);
extern s16 func_ov021_020a89a8(EntryGroupDesc *desc);
extern void func_0202ed9c(void *object, u16 *counter, int arg, int count);
extern fx32 FX_Div_01ff9c84(fx32 numer, fx32 denom);
extern BOOL IsNodeFlagBitClear_020872b8(FieldObject *obj);
extern void func_ov001_0208078c(void *model, u8 modelKind, u8 paletteId, u8 actorId, void *out, int mode, int x, int y, int z, int a, int b, int c);
extern void func_020358b0(int index, u16 *counter, int arg, int count);
extern Actor *func_02036240(u32 id);
extern void RebindAnimTracks_020809d0(void *anim, int blendIndex, int frame);
extern void func_0202f4e8(void *target);
extern void SetScaledPosition_020a34f4(FieldObject *obj, const VecFx32 *position);
extern void func_020359f8(int index, int a, int b);
extern void func_02034050(void *target, int a, int b);
extern void ActorSlot_SetFlag8ByIndex_02036120(int index, BOOL enable);
extern void OffsetBoxByDelta_0203ac70(const void *src, void *dst, const VecFx32 *delta);
extern int func_ov001_02063a38(void);
extern void FieldObject_SetDisabled_020a333c(FieldObject *obj, BOOL disable);
extern void func_020369c8(u32 id, FieldObject *obj, int value);
extern void FieldObject_HandleStrongHit_020a28d4(void);
extern void FieldObject_SpawnContactEffect_020a286c(void);
extern void func_ov001_0207f050(u32 bit);
extern void *NNSi_FndAllocFromDefaultHeap_0202a178(u32 size);
extern void func_0202f4d8(void *object);

static inline HitCallback MakeCallback(void *func, void *context)
{
    HitCallback callback;
    callback.func = func;
    callback.context = context;
    return callback;
}

static inline void ComputeBounds(CollisionShape *shape)
{
    data_020559c0[shape->kind](shape, (s32 *)((u8 *)shape + 4));
}

void LoadKind6ObjectPhase_020a1ef8(FieldObject *obj, int phase, u16 *counter, int arg)
{
    u8 buffer[20];
    EntryGroupDesc desc;
    int kind = obj->kind;
    SceneNode *node = NULL;
    ObjectDef *def = obj->def;
    Actor *actor;
    BOOL enable;

    switch (phase) {
    case 3:
        if (def->nodes[0].loaded == 0) {
            node = &def->nodes[0];
            ZeroBytes0x14_020a8adc(&desc);
            desc.unk_04 = 1;
            desc.unk_08 = 1;
            desc.unk_0c = 0;
            desc.data = data_ov018_020a3850;
            def->effectBank = func_ov021_020a89a8(&desc);
        }
        break;
    case 1:
        if (def->nodes[1].loaded == 0) {
            node = &def->nodes[1];
        }
        break;
    case 10:
        if (def->nodes[2].loaded == 0) {
            node = &def->nodes[2];
        }
        break;
    case 2:
        if (def->nodes[3].loaded == 0) {
            node = &def->nodes[3];
        }
        break;
    }
    if (node != NULL) {
        func_0202ed9c(node, counter, arg, 4);
        node->scale.z = FX_Div_01ff9c84(0x1000, 0x1800);
        node->scale.y = node->scale.z;
        node->scale.x = node->scale.y;
    }
    if (phase == kind) {
        if (obj->flags & 1) {
            func_ov001_0208078c(obj->model, obj->def->modelKind, obj->paletteId, obj->actorId, buffer, 3, 0x1000, 0x1000, 0x1000, 0, 1, 0);
        } else {
            if (obj->state != 0 || !IsNodeFlagBitClear_020872b8(obj)) {
                return;
            }
            func_ov001_0208078c(obj->model, obj->def->modelKind, obj->paletteId, obj->actorId, buffer, -1, 0, 0, 0, 0, 1, 0);
        }
        func_020358b0(obj->actorId, counter, arg, 4);
        (*counter)++;
        actor = func_02036240(obj->actorId);
        RebindAnimTracks_020809d0(&actor->drawFlags, obj->animIndex, 0);
        func_0202f4e8(&actor->drawFlags);
        actor->scale.z = FX_Div_01ff9c84(0x1000, 0x1800);
        actor->scale.y = actor->scale.z;
        actor->scale.x = actor->scale.y;
        SetScaledPosition_020a34f4(obj, &obj->position);
        if (!(actor->flags & 0x20)) {
            actor->unk_80 = 0;
            actor->drawFlags |= 0x20;
        }
        func_020359f8(obj->actorId, 0, 0);
        enable = TRUE;
        func_02034050(actor->collision, 1, 4);
        if ((obj->flags & 8) || obj->state != 0 || !IsNodeFlagBitClear_020872b8(obj)) {
            enable = FALSE;
        }
        ActorSlot_SetFlag8ByIndex_02036120(obj->actorId, enable);
        obj->renderFlags |= 4;
        if (obj->flags & 1) {
            actor->falling = 1;
            actor->delta = data_02053438;
            ComputeBounds(&actor->shape);
            OffsetBoxByDelta_0203ac70(actor->shape.bounds, actor->sweptBounds, &actor->delta);
        }
        if (func_ov001_02063a38() == 7) {
            FieldObject_SetDisabled_020a333c(obj, TRUE);
        }
        func_020369c8(obj->actorId, obj, 0xd);
        switch (obj->kind) {
        case 3:
            actor->hitHandlers[1] = MakeCallback(FieldObject_SpawnContactEffect_020a286c, obj);
            break;
        case 1:
            break;
        case 2:
            actor->hitHandlers[0] = MakeCallback(FieldObject_HandleStrongHit_020a28d4, obj);
            break;
        }
        func_02034050(actor->collision, 3, 0xc);
        func_ov001_0207f050(0xc);
    } else if (phase == 8 && obj->state == 0) {
        obj->resource = NNSi_FndAllocFromDefaultHeap_0202a178(0x104);
        func_0202ed9c(obj->resource, counter, arg, 4);
        RebindAnimTracks_020809d0(obj->resource, 0, 0);
        func_0202f4d8(obj->resource);
        (*counter)++;
    }
}
