#include "nitro/types.h"

typedef struct PanelState {
    u8 pad_00[0xe4];
    int exitStep;
} PanelState;

extern PanelState *data_ov015_0207e960;
extern void func_ov002_02062014(int value);
extern void StartPanelFadeIn(int mode);
extern BOOL func_ov002_0206655c(void);
extern u32 DispatchContextCommand_02066c78(u32 command, u32 value, u32 extra, void *buffer);
extern BOOL PlaySoundEffect_0204d924(int seqArcNo, int index);
extern void func_ov015_02070af8(char nextState);

void UpdatePanelExitSequence_02070b8c(void)
{
    switch (data_ov015_0207e960->exitStep) {
    case 0:
        func_ov002_02062014(1);
        data_ov015_0207e960->exitStep = 10;
        break;
    case 10:
        StartPanelFadeIn(3);
        data_ov015_0207e960->exitStep = 20;
        break;
    case 20:
        if (!func_ov002_0206655c()) {
            break;
        }
        if (DispatchContextCommand_02066c78(5, 0, 0, NULL)) {
            PlaySoundEffect_0204d924(2, 13);
        }
        if (!DispatchContextCommand_02066c78(16, 0, 0, NULL)) {
            func_ov015_02070af8(7);
        } else {
            func_ov015_02070af8(1);
        }
        break;
    }
}
