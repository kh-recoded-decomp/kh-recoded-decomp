#include "nitro/types.h"

typedef struct {
    u16 field0;
    u16 field2;
    u8 field4;
    u8 pad5[2];
    u8 field7;
    u8 pad8[4];
} ConfigBlock;

extern ConfigBlock g_configBlock_02060850;
extern void func_01ff8830(void *dst, int val, unsigned int n);
extern int func_02027348(int a, int b);
extern void SetGlobalPackedBit_02027320(int bitIndex);

void func_02027558(u8 param1)
{
    u32 mode = func_02027348(0x1a00, 2) & 3;
    if (mode == 3) {
        mode = 0;
    }
    func_01ff8830(&g_configBlock_02060850, 0, 0xc);
    g_configBlock_02060850.field0 = (u16)func_02027348(mode * 0xf00 + 0x330b, 10);
    g_configBlock_02060850.field2 = (u16)func_02027348(mode * 0xf00 + 0x3315, 10);
    g_configBlock_02060850.field4 = param1;
    u8 modeByte = (u8)mode;
    g_configBlock_02060850.field7 = (g_configBlock_02060850.field7 & ~3) | (modeByte & 3);
    SetGlobalPackedBit_02027320(0x1a05);
}
