#include "nitro/types.h"

extern void func_ov015_02077978(u32 value);
extern u8 *data_ov015_020812e0;

void func_ov015_020779a4(u32 flags, u32 mode) {
    func_ov015_02077978(flags);
    *(u32 *)(data_ov015_020812e0 + 0xc) = mode;
}
