#include "nitro/types.h"
#include "src/overlays/ov041/StageCaption.h"

extern BOOL func_ov041_020cecac(StageCaption *caption);
extern BOOL func_ov041_020ceb44(StageCaption *caption);
extern void QueueStageCaptionLines(StageCaption *caption);
extern void func_ov041_020ce77c(StageCaption *caption, StageTextLine *line, int palette);
extern void PlaySoundEffect(int seqArcNo, int index);
extern void SetBrightnessAndSyncMain(int brightness);
extern void SetStageCaptionState(StageCaption *caption, int state);

/*
 * Caption state 4: on its first frame lays the requested lines out (or lets one of the special layouts do it),
 * draws them and plays the chime; then fades the screen back in over 10 frames and moves on to state 2.
 */
void StageCaptionState4(StageCaption *caption)
{
    int i;
    int brightness;

    if (caption->unk4c == 0) {
        if (!func_ov041_020cecac(caption) && !func_ov041_020ceb44(caption)) {
            QueueStageCaptionLines(caption);
        }
        for (i = 0; i < caption->queuedCount; i++) {
            func_ov041_020ce77c(caption, &caption->queued[i], 1);
        }
        PlaySoundEffect(0x1a0, 0x2d);
    }
    if (++caption->unk4c >= 10) {
        SetStageCaptionState(caption, 2);
        brightness = 0;
    } else {
        brightness = 16 - caption->unk4c * 16 / 10;
    }
    SetBrightnessAndSyncMain(brightness);
}
