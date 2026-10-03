#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct FieldObject FieldObject;

typedef struct {
    u8 pad_00[0xa4];
    VecFx32 position;
} AnimObject;

typedef struct {
    u8 pad_00[0xc];
    u8 counterId;
    u8 pad_0d[3];
    s32 damage;
} HitInfo;

typedef struct {
    u8 data[0x18];
} DropRequest;

struct FieldObject {
    u8 pad_00[0x30];
    u16 slotFlags;
    u8 actorId;
    u8 pad_33[5];
    VecFx32 position;
    u16 saveGroup;
    u8 saveIndex;
    u8 pad_47;
    AnimObject *anim;
    union {
        struct {
            s8 variant;
            s8 dropIndex;
        } drop;
        void (*onDefeat)(FieldObject *obj);
    } link;
    u16 flags;
    s8 state;
    s8 health;
    s32 hurtTimer;
    u8 pad_58[0x48];
    s32 kind;
};

extern BOOL func_ov001_0208764c(FieldObject *obj, HitInfo *hit);
extern void AddSessionCounter_02063a80(int index, int amount);
extern void func_02036974(int index);
extern void func_0202f4e8(void *anim);
extern u8 *func_02036240(u32 id);
extern void RebindAnimTracks_020809d0(void *anim, int blendIndex, int frame);
extern int func_ov001_02063a38(void);
extern BOOL func_ov018_020a1ee4(FieldObject *obj);
extern void DropRequest_InitKind0_020874fc(DropRequest *request, int dropIndex, int variant, u16 saveGroup, u8 saveIndex);
extern void DropRequest_InitKind1_020874e0(DropRequest *request, int dropIndex, int variant, u16 saveGroup, u8 saveIndex);
extern void GrantEntryUnlockReward_02087518(FieldObject *obj, DropRequest *request);
extern void SpawnSoundSlot_0204da8c(int owner, int kind, VecFx32 *position, int flags);

int FieldObject_TakeDamage_020a229c(FieldObject *obj, HitInfo *hit)
{
    DropRequest request;
    int health;

    if (func_ov001_0208764c(obj, hit)) {
        return 0x10;
    }
    if (obj->kind == 2) {
        return 1;
    }
    if (hit->counterId != 0xff) {
        AddSessionCounter_02063a80(0x1c, 1);
    }
    health = obj->health - hit->damage;
    if (health > 0) {
        obj->health = health;
        obj->hurtTimer = 0x1e000;
        func_02036974(obj->actorId);
        return 0;
    }
    obj->health = 0;
    obj->state = 1;
    obj->anim->position = obj->position;
    func_0202f4e8(obj->anim);
    obj->flags |= 0x20;
    RebindAnimTracks_020809d0(func_02036240(obj->actorId) + 4, 1, 0);
    func_0202f4e8(func_02036240(obj->actorId) + 4);
    obj->flags |= 0x10;
    func_ov001_02063a38();
    obj->slotFlags &= ~0x10;
    obj->slotFlags &= ~8;
    if (obj->flags & 0x40) {
        obj->link.onDefeat(obj);
    } else if (func_ov018_020a1ee4(obj)) {
        if (obj->kind == 10) {
            DropRequest_InitKind0_020874fc(&request, obj->link.drop.dropIndex, obj->link.drop.variant, obj->saveGroup, obj->saveIndex);
        } else {
            DropRequest_InitKind1_020874e0(&request, obj->link.drop.dropIndex, obj->link.drop.variant, obj->saveGroup, obj->saveIndex);
        }
        GrantEntryUnlockReward_02087518(obj, &request);
    }
    func_02036974(obj->actorId);
    SpawnSoundSlot_0204da8c(0, 0x2d, &obj->position, 0);
    return 0;
}
