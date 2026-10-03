#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u16 animId;
    u16 nodeIndex;
    fx32 speed;
    fx32 frame;
    fx32 maxFrame;
} AnimTrack;

typedef struct {
    u8 pad_00[0x58];
    AnimTrack motionTrack;
    u8 pad_68[0xc0 - 0x68];
    u32 flags;
} FieldUnit;

extern int GetFieldUnitActionMotion_020a273c(FieldUnit *unit);
extern void InitAnimTrack_020a2a74(FieldUnit *obj, AnimTrack *track, int nodeIndex, fx32 speed, int animId);

fx32 StartFieldUnitMotion_020a2b38(FieldUnit *unit, fx32 speed, int animId)
{
    if (!(unit->flags & 0x8000)) {
        InitAnimTrack_020a2a74(unit, &unit->motionTrack, GetFieldUnitActionMotion_020a273c(unit), speed, animId);
        unit->flags |= 0x8000;
    }
    return unit->motionTrack.maxFrame;
}
