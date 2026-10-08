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

extern u8 *ActorRegistry_GetEntityByIndex(u32 id);
extern BOOL AdvanceAnimationTracks(void *tracks, int step);
extern void ActorSlot_UnlinkByIndex(int index);

int AdvanceObjectAnimations(Obj *obj)
{
    if ((obj->flags & 0x20) && AdvanceAnimationTracks(obj->anim, 0x1000)) {
        obj->flags &= ~0x20;
    }
    if ((obj->flags & 0x10) && AdvanceAnimationTracks(ActorRegistry_GetEntityByIndex(obj->actorId) + 4, 0x1000)) {
        obj->flags &= ~0x10;
    }
    if (!(obj->flags & 0x30)) {
        obj->state = 2;
        if (!(obj->flags & 1)) {
            ActorSlot_UnlinkByIndex(obj->actorId);
        }
    }
    return 0;
}
