#include "nitro/types.h"

extern void DisableOv038Sound_020ba5b4(void);
extern void EnableOv038SoundCtx_020ba52c(void);
extern void MarkSoundCtxRepeatIfReady_020ba58c(void);
extern void TryMarkSoundCtxActive_020ba4f8(void);
extern void func_ov038_020ba568(void);
extern void func_ov038_020ba5f4(void);

void (*data_ov038_020bbd98[6])(void) = {
    TryMarkSoundCtxActive_020ba4f8,
    EnableOv038SoundCtx_020ba52c,
    func_ov038_020ba568,
    MarkSoundCtxRepeatIfReady_020ba58c,
    DisableOv038Sound_020ba5b4,
    func_ov038_020ba5f4,
};
