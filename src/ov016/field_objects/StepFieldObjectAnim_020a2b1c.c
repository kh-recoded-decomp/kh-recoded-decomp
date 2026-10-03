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
    u8 pad_00[0x48];
    AnimTrack track;
} FieldObject;

extern BOOL AdvanceAnimTrack_020a2a94(FieldObject *obj, AnimTrack *track);

BOOL StepFieldObjectAnim_020a2b1c(FieldObject *obj)
{
    return AdvanceAnimTrack_020a2a94(obj, &obj->track);
}
