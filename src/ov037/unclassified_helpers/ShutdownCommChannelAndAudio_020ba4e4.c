#include "nitro/types.h"

typedef struct CommState {
    u8 pad_00[0x14];
    s32 handle;
} CommState;

extern CommState *g_commState_020bb760;
extern void SetSoundListenersEnabled_0204df9c(int enabled);
extern void func_ov001_0206a714(void);
extern void func_ov001_02063c54(void);
extern void SetParamHalf18_02050630(u16 value);
extern void SetParamWord20_02050640(int value);

void ShutdownCommChannelAndAudio_020ba4e4(void)
{
    SetSoundListenersEnabled_0204df9c(0);
    if (g_commState_020bb760->handle != -1) {
        func_ov001_0206a714();
        g_commState_020bb760->handle = -1;
    }
    func_ov001_02063c54();
    SetParamHalf18_02050630(0);
    SetParamWord20_02050640(0);
    g_commState_020bb760 = 0;
}
