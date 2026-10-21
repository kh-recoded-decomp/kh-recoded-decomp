#include "nitro/types.h"

extern void func_ov001_0206a72c(int arg);
extern void FadeBgmVolume(int targetVolume, int frames);
extern void SetStageState(int state, BOOL runNow);

/* Stage state 3: fades the music down and moves on to state 4 at once. */
void StageStateFadeBgm(void)
{
    func_ov001_0206a72c(2);
    FadeBgmVolume(0x7f, 15);
    SetStageState(4, TRUE);
}
