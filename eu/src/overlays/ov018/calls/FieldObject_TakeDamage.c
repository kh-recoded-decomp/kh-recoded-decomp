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

extern BOOL func_ov001_02087674(FieldObject *obj, HitInfo *hit);
extern void AddSessionCounter(int index, int amount);
extern void ClearRecordSlotFlag(int index);
extern void Flags16_ClearBit1(void *anim);
extern u8 *ActorRegistry_GetEntityByIndex(u32 id);
extern void RebindAnimTracks(void *anim, int blendIndex, int frame);
extern int func_ov001_02063a38(void);
extern BOOL func_ov018_020a1f04(FieldObject *obj);
extern void DropRequest_InitKind0(DropRequest *request, int dropIndex, int variant, u16 saveGroup, u8 saveIndex);
extern void DropRequest_InitKind1(DropRequest *request, int dropIndex, int variant, u16 saveGroup, u8 saveIndex);
extern void GrantEntryUnlockReward(FieldObject *obj, DropRequest *request);
extern void SpawnSoundSlot(int owner, int kind, VecFx32 *position, int flags);

int FieldObject_TakeDamage(FieldObject *obj, HitInfo *hit)
{
    DropRequest request;
    int health;

    if (func_ov001_02087674(obj, hit)) {
        return 0x10;
    }
    if (obj->kind == 2) {
        return 1;
    }
    if (hit->counterId != 0xff) {
        AddSessionCounter(0x1c, 1);
    }
    health = obj->health - hit->damage;
    if (health > 0) {
        obj->health = health;
        obj->hurtTimer = 0x1e000;
        ClearRecordSlotFlag(obj->actorId);
        return 0;
    }
    obj->health = 0;
    obj->state = 1;
    obj->anim->position = obj->position;
    Flags16_ClearBit1(obj->anim);
    obj->flags |= 0x20;
    RebindAnimTracks(ActorRegistry_GetEntityByIndex(obj->actorId) + 4, 1, 0);
    Flags16_ClearBit1(ActorRegistry_GetEntityByIndex(obj->actorId) + 4);
    obj->flags |= 0x10;
    func_ov001_02063a38();
    obj->slotFlags &= ~0x10;
    obj->slotFlags &= ~8;
    if (obj->flags & 0x40) {
        obj->link.onDefeat(obj);
    } else if (func_ov018_020a1f04(obj)) {
        if (obj->kind == 10) {
            DropRequest_InitKind0(&request, obj->link.drop.dropIndex, obj->link.drop.variant, obj->saveGroup, obj->saveIndex);
        } else {
            DropRequest_InitKind1(&request, obj->link.drop.dropIndex, obj->link.drop.variant, obj->saveGroup, obj->saveIndex);
        }
        GrantEntryUnlockReward(obj, &request);
    }
    ClearRecordSlotFlag(obj->actorId);
    SpawnSoundSlot(0, 0x2d, &obj->position, 0);
    return 0;
}
