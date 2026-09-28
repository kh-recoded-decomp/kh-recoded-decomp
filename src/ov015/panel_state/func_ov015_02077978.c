#include "nitro/types.h"

extern void func_ov015_0207793c(void);
extern u8 *data_ov015_020812e0;

void func_ov015_02077978(u32 value) {
    *(u32 *)(data_ov015_020812e0 + 8) = value;
    func_ov015_0207793c();
    *(u32 *)(data_ov015_020812e0 + 0x18) &= 0xfffeffff;
}
