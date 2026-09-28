typedef unsigned int u32;
u32 func_ov001_020925c8(u32 argument0, u32 argument1, u32 argument2, u32 argument3) {
    u32 value0 = *(const unsigned short *)((argument0 + 0x6U));
    u32 value1 = 0x1U;
    u32 value2 = (value1) << 14;
    u32 value3 = (value2) | (value0);
    *(unsigned char *)((argument0 + 0xbU)) = argument1;
    *(unsigned short *)((argument0 + 0x6U)) = value3;
    u32 value6 = (argument1) + (0x0U);
    return value6;
}
