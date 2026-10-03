#include "nitro/types.h"

typedef struct ConnectState {
    u8 pad_00[0x79];
    u8 lowFlags : 4;
    u8 isHost : 1;
} ConnectState;

extern ConnectState *data_ov015_0207e964;
extern u32 GetPanelTransitionMode_020748e4(void);
extern void PollPanelTransition_02074e80(void);
extern void func_ov015_02074c24(void);
extern unsigned int func_0202a9d0(unsigned int range);
extern void func_ov015_02072ee4(char nextState);

void HandleMatchTransition_02073034(void)
{
    switch (GetPanelTransitionMode_020748e4()) {
    case 9:
    case 10:
        PollPanelTransition_02074e80();
        break;
    case 1:
        if (data_ov015_0207e964->isHost) {
            break;
        }
        func_ov015_02074c24();
        if (func_0202a9d0(100) < 50) {
            func_ov015_02072ee4(4);
        } else {
            func_ov015_02072ee4(5);
        }
        break;
    }
}
