#include "nitro/types.h"

typedef struct {
    u8 pad_00[0xe0];
    u8 lowBits : 3;
    u8 panelActive : 1;
    u8 highBits : 4;
    u8 pad_e1[3];
    u32 exitRequest;
} PanelState;

extern void func_ov015_0206d59c(void);
extern void func_ov015_0206edc8(void);
extern PanelState *data_ov015_0207e960;

void func_ov015_02070fb4(void) {
    func_ov015_0206d59c();
    func_ov015_0206edc8();
    data_ov015_0207e960->panelActive = 0;
    data_ov015_0207e960->exitRequest = 0;
}
