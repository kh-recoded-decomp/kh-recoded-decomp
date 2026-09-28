typedef unsigned int u32;
u32 func_ov037_020baa3c(u32 argument0, u32 argument1, u32 argument2, u32 argument3) {
    u32 value0 = 0x20bb760U;
    u32 value1 = 0xfff3U;
    u32 value2 = *(const u32 *)(value0);
    u32 value3 = ~(0x0U);
    u32 value4 = *(const unsigned short *)((value2 + 0x6U));
    u32 value5 = (value4) & (value1);
    *(unsigned short *)((value2 + 0x6U)) = value5;
    return value3;
}
