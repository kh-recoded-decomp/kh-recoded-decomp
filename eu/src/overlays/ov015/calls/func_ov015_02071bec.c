#include "nitro/types.h"

typedef struct {
    u8 pad_00[0xe1];
    u8 bits0_2 : 3;
    u8 flagE1_3 : 1;
    u8 flagE1_4 : 1;
    u8 bits5_6 : 2;
    u8 flagE1_7 : 1;
    u8 bitE2_0 : 1;
    u8 flagE2_1 : 1;
    u8 bitsE2_2_7 : 6;
} PanelState;

extern u32 func_ov015_02075320(void);
extern void ReleaseWorkBuffer(void);
extern void func_ov002_02062368(void);
extern void func_ov002_020620fc(int selector);
extern void func_ov015_02070af8(int mode);
extern PanelState *data_ov015_0207e960;

void func_ov015_02071bec(void) {
    if (func_ov015_02075320() != 0) {
        return;
    }
    ReleaseWorkBuffer();
    data_ov015_0207e960->flagE1_3 = 0;
    data_ov015_0207e960->flagE2_1 = 0;
    data_ov015_0207e960->flagE1_4 = 0;
    data_ov015_0207e960->flagE1_7 = 0;
    func_ov002_02062368();
    func_ov002_020620fc(0);
    func_ov015_02070af8(2);
}
