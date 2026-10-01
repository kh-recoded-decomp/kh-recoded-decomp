#include "nitro/types.h"
#include "nitro/fx_types.h"

struct FieldObject;

typedef struct TriggerLink {
    u8 kind;
    u8 pad_01;
    u16 arg;
} TriggerLink;

typedef struct HitInfo {
    u8 pad_00[0xc];
    u8 dropSlot;
    u8 pad_0D[3];
    s32 damage;
} HitInfo;

typedef BOOL (*HitHandler)(void *context, struct FieldObject *object, u16 arg, HitInfo *hit);

typedef struct FieldManager {
    u8 pad_000[0x1b0];
    HitHandler hitHandlers[1];
} FieldManager;

typedef struct FieldObject {
    u8 pad_00[4];
    FieldManager *manager;
    u8 pad_08[0x28];
    u16 statusFlags;
    u8 slot;
    u8 pad_33[5];
    VecFx32 position;
    u16 dropGroup;
    u8 dropIndex;
    u8 pad_47;
    s8 dropVariant;
    s8 dropItem;
    s8 state;
    u8 flags : 7;
    u8 flagsHigh : 1;
    u8 pad_4C[4];
    s32 kind : 16;
    s32 subKind : 12;
    s32 bit28 : 1;
    s32 hitsLeft : 3;
    u8 pad_54[0xc];
    TriggerLink *trigger;
    u8 pad_64[4];
    s32 timer;
    u8 pad_6C[4];
    u8 context[4];
} FieldObject;

typedef struct DropRequest {
    u8 data[0x18];
} DropRequest;

extern BOOL func_ov001_0208764c(void);
extern s8 GetCtxModeByte_02068084(void);
extern BOOL func_ov016_020a2bb0(FieldObject *object);
extern void func_ov001_02063a80(int id, int arg);
extern u8 *func_02036240(int slot);
extern void func_ov001_020809d0(void *anim, int animId, int arg);
extern void func_0202f4e8(void *anim);
extern void DropRequest_InitKind0_020874fc(DropRequest *request, int dropItem, int variant, u16 group, u8 index);
extern void DropRequest_InitKind1_020874e0(DropRequest *request, int dropItem, int variant, u16 group, u8 index);
extern void func_ov001_02087518(FieldObject *object, DropRequest *request);
extern void func_ov001_020665bc(int variant, VecFx32 *position);
extern void func_02036974(int slot);
extern void func_0204da8c(int bank, int soundId, VecFx32 *position, int arg);

int func_ov017_020a2f08(FieldObject *object, HitInfo *hit)
{
    FieldManager *manager = object->manager;
    TriggerLink *trigger;
    HitHandler handler;
    DropRequest request;

    if (func_ov001_0208764c()) {
        return 0x10;
    }
    trigger = object->trigger;
    if (trigger != NULL) {
        handler = manager->hitHandlers[trigger->kind];
        if (handler != NULL && !handler(object->context, object, trigger->arg, hit)) {
            return 0x10;
        }
    }
    if (object->kind == 2 || (object->kind == 3 && GetCtxModeByte_02068084() == 6)) {
        if (hit->damage < 0x7fffffff) {
            return 1;
        }
    }
    if (hit->dropSlot == 0xff) {
        if (func_ov016_020a2bb0(object)) {
            return 0x10;
        }
    } else if (object->kind != 2) {
        func_ov001_02063a80(0x1c, 1);
    }
    object->hitsLeft--;
    if (object->hitsLeft != 0) {
        return 0;
    }
    object->state = 1;
    object->timer = 0;
    object->flags |= 8;
    func_ov001_020809d0(func_02036240(object->slot) + 4, 1, 0);
    func_0202f4e8(func_02036240(object->slot) + 4);
    object->flags |= 4;
    object->timer = 0x1f;
    object->statusFlags &= ~0x10;
    object->statusFlags &= ~8;
    if (!(object->flags & 0x10) && hit->dropSlot != 0xff) {
        if (object->dropItem >= 0 || object->dropVariant >= 0) {
            if (object->kind == 10) {
                DropRequest_InitKind0_020874fc(&request, object->dropItem, object->dropVariant, object->dropGroup, object->dropIndex);
            } else {
                DropRequest_InitKind1_020874e0(&request, object->dropItem, object->dropVariant, object->dropGroup, object->dropIndex);
            }
            func_ov001_02087518(object, &request);
            if (object->dropItem >= 0 && object->dropVariant >= 0) {
                func_ov001_020665bc(object->dropVariant, &object->position);
            }
        }
    }
    func_02036974(object->slot);
    func_0204da8c(0, 0x2d, &object->position, 0);
    return 0;
}
