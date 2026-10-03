#include "nitro/types.h"

typedef struct FieldNode {
    u8 pad_00[8];
    u16 flags;
} FieldNode;

typedef struct FieldObject {
    u8 pad_00[8];
    FieldNode *node;
    u8 pad_0C[0x24];
    u16 statusFlags;
    u8 slot;
    u8 pad_33[0x14];
    s8 idleAnim;
    u8 pad_48[2];
    s8 state;
    u8 flags : 7;
    u8 flagsHigh : 1;
    u8 pad_4C[4];
    s32 kind : 16;
    s32 subKind : 12;
    s32 bit28 : 1;
    s32 hitsLeft : 3;
    u8 pad_54[0x14];
    s32 timer;
} FieldObject;

extern u8 *func_02036240(int slot);
extern void RebindAnimTracks_020809d0(void *anim, int blendIndex, int frame);
extern void func_0202f4e8(void *anim);
extern void selectJointAnimationBlend_0202f2cc(void *anim, u16 trackIndex, void *blendTable, short blendIndex);
extern void func_ov017_020a3c78(FieldObject *object, int arg);
extern void ActorSlot_SetFlag8ByIndex_02036120(int index, BOOL enable);
extern void CacheEntry_SetActive_02087258(FieldObject *object, BOOL active);
extern u16 GetSavedStateValue_0208645c(FieldObject *object);
extern void SetSavedStateValue_0208647c(FieldObject *object, u16 value);
extern void func_02036924(int index);

void ResetFieldObjectToIdle_020a3e10(FieldObject *object)
{
    u8 *actor;

    object->state = 0;
    actor = func_02036240(object->slot);
    RebindAnimTracks_020809d0(actor + 4, object->idleAnim, 0);
    func_0202f4e8(actor + 4);
    selectJointAnimationBlend_0202f2cc(actor + 4, 2, actor + 0xdc, -1);
    if (object->flags & 2) {
        func_ov017_020a3c78(object, 0);
    } else {
        ActorSlot_SetFlag8ByIndex_02036120(object->slot, TRUE);
        CacheEntry_SetActive_02087258(object, TRUE);
    }
    SetSavedStateValue_0208647c(object, GetSavedStateValue_0208645c(object) & ~1);
    if (!(object->node->flags & 0x100)) {
        func_02036924(object->slot);
    }
    object->hitsLeft = 1;
    object->timer = 0;
    object->bit28 = 1;
    object->statusFlags |= 0x10;
}
