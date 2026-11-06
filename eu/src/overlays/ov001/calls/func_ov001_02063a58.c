#include "nitro/types.h"

extern u32 gFieldSessionWork;

void func_ov001_02063a58(u8 value) {
    *(u8 *)(gFieldSessionWork + 0x27b4) = value;
}
