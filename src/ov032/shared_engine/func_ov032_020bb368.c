#include "nitro/types.h"

extern void func_020360a0(s32 channelMask);
extern void func_ov001_020668e4(void);
extern void func_ov001_02067d80(s32 channelMask);
extern void func_ov001_0206d95c(s32 channelMask);
extern void func_ov001_0207ecc4(s32 channelMask);
extern void func_ov001_02087694(s32 channelMask);

void func_ov032_020bb368(s32 keepAlive) {
    if (keepAlive == 0) {
        func_ov001_02067d80(0x1000);
        func_ov001_0207ecc4(0x1000);
    }
    func_ov001_0206d95c(0x1000);
    if (keepAlive == 0) {
        func_ov001_02087694(0x1000);
        func_ov001_020668e4();
    }
    func_020360a0(0x1000);
}
