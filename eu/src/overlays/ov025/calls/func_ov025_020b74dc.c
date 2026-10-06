typedef unsigned int u32;
u32 func_ov025_020b74dc(u32 argument0, u32 argument1, u32 argument2, u32 argument3) {
    u32 value0 = *(const u32 *)((argument0 + 0x4U));
    u32 value1 = (argument0) + (0xa4U);
    u32 value2 = *(const u32 *)(value1);
    u32 value3 = *(const u32 *)((value0 + 0x4U));
    u32 value4 = (value2) << 3;
    u32 value5 = (value3) + (value4);
    u32 value6 = *(const unsigned short *)((value5 + 0xaU));
    u32 value7 = (value6) - (0x2U);
    u32 value8 = (u32)((int)(value7) >> 3);
    u32 value9 = (value8) >> 28;
    u32 value10 = (value7) + (value9);
    u32 value11 = (u32)((int)(value10) >> 4);
    return value11;
}
