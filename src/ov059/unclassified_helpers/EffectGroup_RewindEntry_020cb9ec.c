#include "nitro/types.h"

extern void *func_ov021_020a8eec(s32 groupId, s32 entryIndex);
extern int *func_01ffb2f8(void *animObject, int track, int frame);
extern void StopAndClearSoundEmitter_020a8e14(s32 groupId, s32 emitterIndex);

void EffectGroup_RewindEntry_020cb9ec(s32 groupId, s32 entryIndex)
{
    void *animObject = func_ov021_020a8eec(groupId, entryIndex);

    func_01ffb2f8(animObject, 0, 0);
    func_01ffb2f8(animObject, 2, 0);
    StopAndClearSoundEmitter_020a8e14(groupId, 0);
}
