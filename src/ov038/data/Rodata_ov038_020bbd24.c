#include "nitro/types.h"

extern void AdvanceOv038ExitTimer_020babb4(void);
extern void HandleOv038PageInput_020baa98(void);
extern void ShowOv038ResultsFadeIn_020ba768(void);
extern void StopOv038SoundStream_020bac24(void);
extern void func_ov038_020ba760(void);

void (*const data_ov038_020bbd24[5])(void) = {
    func_ov038_020ba760,
    ShowOv038ResultsFadeIn_020ba768,
    HandleOv038PageInput_020baa98,
    AdvanceOv038ExitTimer_020babb4,
    StopOv038SoundStream_020bac24,
};
