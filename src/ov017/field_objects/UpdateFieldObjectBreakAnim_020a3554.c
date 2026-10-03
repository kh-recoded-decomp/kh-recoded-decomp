#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct FieldManager {
    u8 pad_00[0x6c];
    u8 breakAnim[4];
} FieldManager;

typedef struct FieldObject {
    u8 pad_00[4];
    FieldManager *manager;
    u8 pad_08[0x2a];
    u8 slot;
    u8 pad_33[0x17];
    s8 state;
    u8 flags : 7;
    u8 flagsHigh : 1;
    u8 pad_4C[0x1c];
    fx32 timer;
} FieldObject;

extern fx32 func_0202f4b8(void *anim, int track);
extern u8 *func_02036240(int slot);
extern BOOL AdvanceAnimationTracks_0202ef24(void *animation, fx32 step);
extern void ActorSlot_UnlinkByIndex_02035c28(int index);

int UpdateFieldObjectBreakAnim_020a3554(FieldObject *object)
{
    FieldManager *manager = object->manager;

    if (object->flags & 8) {
        object->timer += 0x1000;
        if (object->timer >= func_0202f4b8(manager->breakAnim, 0)) {
            object->flags &= ~8;
        }
    }
    if ((object->flags & 4) && AdvanceAnimationTracks_0202ef24(func_02036240(object->slot) + 4, 0x1000)) {
        object->flags &= ~4;
    }
    if (!(object->flags & 0xc)) {
        object->state = 2;
        if (!(object->flags & 1)) {
            ActorSlot_UnlinkByIndex_02035c28(object->slot);
        }
    }
    return 0;
}
