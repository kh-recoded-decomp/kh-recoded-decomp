#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x32];
    u8 actorId;
    u8 pad_33[0x15];
    void *anim;
    u8 pad_4c[4];
    u16 flags;
    s8 state;
} Obj;

extern u8 *func_02036240(u32 id);
extern BOOL AdvanceAnimationTracks_0202ef24(void *tracks, int step);
extern void ActorSlot_UnlinkByIndex_02035c28(int index);

int AdvanceObjectAnimations_020a2bf8(Obj *obj)
{
    if ((obj->flags & 0x20) && AdvanceAnimationTracks_0202ef24(obj->anim, 0x1000)) {
        obj->flags &= ~0x20;
    }
    if ((obj->flags & 0x10) && AdvanceAnimationTracks_0202ef24(func_02036240(obj->actorId) + 4, 0x1000)) {
        obj->flags &= ~0x10;
    }
    if (!(obj->flags & 0x30)) {
        obj->state = 2;
        if (!(obj->flags & 1)) {
            ActorSlot_UnlinkByIndex_02035c28(obj->actorId);
        }
    }
    return 0;
}
