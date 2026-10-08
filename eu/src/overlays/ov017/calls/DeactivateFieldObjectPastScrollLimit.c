#include "nitro/types.h"

typedef struct FieldObjectWork {
    u8 pad_00[0x32];
    u8 actorSlot;
    u8 pad_33[5];
    s32 position;
} FieldObjectWork;

extern void ActorSlot_SetFlag8ByIndex(u32 index, int enabled);
extern void ActorSlot_UnlinkByIndex(u32 index);
extern void CacheEntry_SetActive(FieldObjectWork *work, int active);
extern u32 FollowChainLeader(void);
extern s32 *Camera_GetGoalPosition(void);
extern s32 *func_ov042_020bd5b0(void);

u32 DeactivateFieldObjectPastScrollLimit(FieldObjectWork *work)
{
    u32 flags;
    s32 *origin;
    s32 *extent;

    flags = FollowChainLeader();
    if ((flags & 1) == 0) {
        origin = Camera_GetGoalPosition();
        extent = func_ov042_020bd5b0();
        if (work->position - *origin < *extent * 3) {
            ActorSlot_SetFlag8ByIndex(work->actorSlot, 0);
            ActorSlot_UnlinkByIndex(work->actorSlot);
            CacheEntry_SetActive(work, 0);
        }
    }
    return 0;
}
