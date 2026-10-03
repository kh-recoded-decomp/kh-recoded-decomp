#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct TouchHandler {
    u32 words[5];
} TouchHandler;

typedef struct {
    u8 pad_00[0x59];
    u8 kind;
} ObjectDef;

typedef struct FieldObject {
    u8 pad_00[4];
    ObjectDef *def;
    u8 pad_08[4];
    void (*update)(void);
    u8 pad_10[0x20];
    u16 slotFlags;
    u8 actorId;
    u8 pad_33;
    fx32 speed;
    VecFx32 position;
    u16 packedLow;
    u8 packedHigh;
    u8 unk_47;
    s32 unk_48;
    s8 linkIndex;
    s8 linkGroup;
    u8 pad_4e[2];
    u16 flags;
    s8 state;
    u8 pad_53[0x4d];
    s32 kind;
    u8 pad_a4[4];
    TouchHandler touch;
} FieldObject;

extern FieldObject *func_ov001_02086308(void *manager);
extern void ResetKindDirection_020a1ebc(FieldObject *obj);
extern void AppendNodeToActiveList_02086fac(int kind, int objectId, int slot);
extern int func_ov001_02063a38(void);
extern void func_ov018_020a2c84(void);
extern void func_ov018_020a29e0(FieldObject *obj);
extern TouchHandler func_ov031_020bc5b0(void (*callback)(FieldObject *), FieldObject *owner, int mode, int flags);
extern void func_ov031_020bc5e0(TouchHandler *handler);

u8 CreateKind6FieldObject_020a3234(void *manager, u16 objectId, int slot, u16 packedLow, u8 packedHigh, VecFx32 *position,
                       s8 linkIndex, s8 linkGroup, fx32 speed)
{
    FieldObject *obj = func_ov001_02086308(manager);
    ObjectDef *def = obj->def;

    obj->position = *position;
    obj->packedLow = packedLow;
    obj->packedHigh = packedHigh;
    obj->unk_47 = 0;
    obj->speed = speed;
    obj->state = 0;
    obj->flags = 0;
    obj->unk_48 = 0;
    obj->linkIndex = linkIndex;
    obj->linkGroup = linkGroup;
    obj->flags |= 1;
    if (obj->state != 0) {
        obj->update = NULL;
        obj->state = 2;
    } else {
        obj->update = func_ov018_020a2c84;
        obj->slotFlags |= 8;
        obj->slotFlags |= 0x10;
    }
    if (obj->linkGroup >= 0) {
        obj->kind = 1;
    } else {
        obj->kind = 3;
    }
    ResetKindDirection_020a1ebc(obj);
    obj->actorId = slot;
    AppendNodeToActiveList_02086fac(def->kind, objectId, obj->actorId);
    if (func_ov001_02063a38() == 7) {
        obj->touch = func_ov031_020bc5b0(func_ov018_020a29e0, obj, 2, 0);
        func_ov031_020bc5e0(&obj->touch);
    }
    return obj->actorId;
}







