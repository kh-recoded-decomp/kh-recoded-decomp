#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct ShapeParams {
    u32 flags;
    fx32 extentA;
    fx32 extentB;
    fx32 extentC;
    fx32 extentD;
} ShapeParams;

typedef struct ShapeDesc {
    u16 flags;
    u16 group;
    fx32 extentA;
    fx32 extentB;
    fx32 extentC;
    fx32 extentD;
} ShapeDesc;

typedef struct ActorEntry {
    u8 pad_000[8];
    u16 flags;
    u8 pad_00A[2];
    s8 priority;
    u8 pad_00D[3];
    u8 object[0x194];
    u8 attributes[4];
    u8 pad_1A8[0x1c];
    s16 animSpeed;
    u8 pad_1C6[2];
    void (*draw)(struct ActorEntry *entry, BOOL useOverride);
    void (*update)(struct ActorEntry *entry, fx32 deltaTime);
} ActorEntry;

extern void func_02036850(ActorEntry *entry, int slot);
extern BOOL Obj_InitLinkState_0203538c(void *object);
extern BOOL func_02035458(void *object, ShapeDesc *desc);
extern void func_020369f4(ActorEntry *entry, BOOL useOverride);
extern void func_02036a34(ActorEntry *entry, fx32 deltaTime);

void ActorEntry_Init_020357d8(int slot, ActorEntry *entry, u16 group, const u8 *attributes, const ShapeParams *shape, BOOL flag20, s8 priority)
{
    ShapeDesc desc;

    if (slot != 0xffff) {
        func_02036850(entry, slot);
    }
    Obj_InitLinkState_0203538c(entry->object);
    if (shape != NULL) {
        desc.flags = shape->flags;
        desc.group = group;
        desc.extentA = shape->extentA;
        desc.extentB = shape->extentB;
        desc.extentA = shape->extentA;
        desc.extentC = shape->extentC;
        desc.extentD = shape->extentD;
        func_02035458(entry->object, &desc);
    }
    if (attributes != NULL) {
        entry->attributes[0] = attributes[0];
        entry->attributes[1] = attributes[1];
        entry->attributes[2] = attributes[2];
        entry->attributes[3] = attributes[3];
    }
    entry->flags |= 1;
    if (flag20) {
        entry->flags |= 0x20;
    } else {
        entry->flags &= ~0x20;
    }
    entry->animSpeed = 0x1000;
    entry->priority = priority;
    entry->draw = func_020369f4;
    entry->update = func_02036a34;
}
