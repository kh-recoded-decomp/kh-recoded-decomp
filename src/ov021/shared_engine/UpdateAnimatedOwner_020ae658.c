#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct AnimOwner {
    u8 pad0[2];
    s8 phase;
    u8 pad3;
    int elapsed;
    u8 pad8[0xcc];
    VecFx32 position;
} AnimOwner;

typedef struct SpawnWork {
    u8 data[0xd4];
} SpawnWork;

extern void func_ov021_020ab0c8(SpawnWork *work, void *source, AnimOwner *owner, VecFx32 *position, VecFx32 *offset);
extern int AdvanceOwnerAnimation_020ab41c(AnimOwner *owner, int step);
extern void AdvanceToSecondPhase_020ab5f0(AnimOwner *owner);

BOOL UpdateAnimatedOwner_020ae658(void *source, AnimOwner *owner, int step)
{
    SpawnWork work;
    VecFx32 position;
    VecFx32 offset;

    position = owner->position;
    offset.z = 0;
    offset.y = 0;
    offset.x = 0;
    if (owner->elapsed == 0) {
        func_ov021_020ab0c8(&work, source, owner, &position, &offset);
    }
    owner->elapsed += step;
    if (owner->phase == 1 && (u16)AdvanceOwnerAnimation_020ab41c(owner, step) != 0) {
        AdvanceToSecondPhase_020ab5f0(owner);
    }
    if (owner->phase == -1) {
        return TRUE;
    }
    return FALSE;
}
