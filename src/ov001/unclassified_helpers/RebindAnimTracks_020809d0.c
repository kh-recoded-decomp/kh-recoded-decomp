#include "nitro/types.h"

extern void selectJointAnimationBlend_0202f2cc(void *anim, u16 trackIndex, void *blendTable, short blendIndex);
extern void *func_01ffb2f8(void *anim, u16 trackIndex, int frame);

void RebindAnimTracks_020809d0(s16 *anim, int blendIndex, int frame)
{
    int track;

    for (track = 0; track < 5; track++) {
        u16 trackIndex = (u16)track;

        if (anim[trackIndex + 0x6C] > 0) {
            selectJointAnimationBlend_0202f2cc(anim, trackIndex, anim + 0x6C, blendIndex);
            func_01ffb2f8(anim, (u16)track, frame);
        }
    }
}
