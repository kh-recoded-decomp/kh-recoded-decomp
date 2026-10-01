#include "nitro/types.h"

typedef struct Ov101State {
    u8 pad_0000[0xCFC4];
    int frameCounter;
    int secondToggle;
} Ov101State;

typedef void (*PhaseHandler)(Ov101State *state);

extern u32 func_ov101_020c0c3c(void);
extern void func_ov101_020bf634(int index, Ov101State *state);
extern void InitStateLists_020bfa4c(Ov101State *state);
extern void func_ov101_020c0710(Ov101State *state);
extern PhaseHandler data_ov101_020c0da0[];

void UpdateStateFrame_020bed04(Ov101State *state)
{
    PhaseHandler handler = data_ov101_020c0da0[func_ov101_020c0c3c()];
    if (handler != NULL) {
        handler(state);
    }
    if (++state->frameCounter >= 60) {
        state->frameCounter = 0;
        state->secondToggle = (state->secondToggle + 1) % 2;
        func_ov101_020bf634(0, state);
    }
    InitStateLists_020bfa4c(state);
    func_ov101_020c0710(state);
}
