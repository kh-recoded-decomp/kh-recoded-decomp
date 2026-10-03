#include "nitro/types.h"

typedef struct Ov039State {
    u8 pad_0000[0xc998];
    void *primaryWork;
    void *secondaryWork;
    u8 pad_c9a0[0x70];
    BOOL inputEnabled;
    u8 pad_ca14[4];
    BOOL primaryActive;
    BOOL secondaryActive;
    u16 buttonState;
    u8 pad_ca22[0x1a];
    BOOL inputBlocked;
    u8 pad_ca40[0xa];
    u16 inputSource;
} Ov039State;

extern Ov039State *data_ov039_020bea00;
extern u16 data_02060500;

extern u16 func_0204f5ec(const u16 *source);
extern int dispatch_input_handler_pair_14_020bd084(void *primary, void *secondary);
extern int DispatchOverlayEventPairA_020bd0fc(void *primary, void *secondary);
extern int dispatchMenuHandlerPairAt1c_020bd174(void *primary, void *secondary);
extern int dispatch_input_handler_pair_20_020bd1ec(void *primary, void *secondary);
extern int DispatchOverlayEventPairB_020bd264(void *primary, void *secondary);
extern int dispatchMenuHandlerPairAt28_020bd2dc(void *primary, void *secondary);
extern int dispatch_input_handler_pair_2c_020bd354(void *primary, void *secondary);
extern int DispatchOverlayEventPairC_020bd3cc(void *primary, void *secondary);
extern int dispatchMenuHandlerPairAt34_020bd444(void *primary, void *secondary);
extern int dispatch_input_handler_pair_38_020bd4bc(void *primary, void *secondary);
extern int DispatchOverlayEventPairD_020bd534(void *primary, void *secondary);
extern int dispatchMenuHandlerPairAt40_020bd5ac(void *primary, void *secondary);

void PollHandlerInput_020baf1c(void)
{
    Ov039State *state = data_ov039_020bea00;
    void *primary = state->primaryActive ? state->primaryWork : NULL;
    void *secondary = state->secondaryActive ? state->secondaryWork : NULL;

    if (state->inputEnabled == 0) {
        return;
    }
    if (state->inputBlocked == 0) {
        if ((func_0204f5ec(&state->inputSource) & 0x40) && dispatch_input_handler_pair_14_020bd084(primary, secondary)) {
            return;
        }
        if ((func_0204f5ec(&state->inputSource) & 0x80) && DispatchOverlayEventPairA_020bd0fc(primary, secondary)) {
            return;
        }
        if ((func_0204f5ec(&state->inputSource) & 0x20) && dispatchMenuHandlerPairAt1c_020bd174(primary, secondary)) {
            return;
        }
        if ((func_0204f5ec(&state->inputSource) & 0x10) && dispatch_input_handler_pair_20_020bd1ec(primary, secondary)) {
            return;
        }
        if ((data_02060500 & 0x1) && DispatchOverlayEventPairB_020bd264(primary, secondary)) {
            return;
        }
        if ((data_02060500 & 0x2) && dispatchMenuHandlerPairAt28_020bd2dc(primary, secondary)) {
            return;
        }
        if ((data_02060500 & 0x400) && dispatch_input_handler_pair_2c_020bd354(primary, secondary)) {
            return;
        }
        if ((data_02060500 & 0x800) && DispatchOverlayEventPairC_020bd3cc(primary, secondary)) {
            return;
        }
        if ((data_02060500 & 0x200) && dispatchMenuHandlerPairAt34_020bd444(primary, secondary)) {
            return;
        }
        if ((data_02060500 & 0x100) && dispatch_input_handler_pair_38_020bd4bc(primary, secondary)) {
            return;
        }
        if ((data_02060500 & 0x4) && DispatchOverlayEventPairD_020bd534(primary, secondary)) {
            return;
        }
        if ((data_02060500 & 0x8) && dispatchMenuHandlerPairAt40_020bd5ac(primary, secondary)) {
            return;
        }
    }
    state->buttonState = (data_02060500 & 0x2f0f) | (func_0204f5ec(&state->inputSource) & 0xf0);
}
