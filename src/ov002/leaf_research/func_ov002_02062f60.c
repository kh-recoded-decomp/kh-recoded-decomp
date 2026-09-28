typedef unsigned int u32;
u32 func_ov002_02062f60(u32 argument0, u32 argument1, u32 argument2, u32 argument3) {
    u32 value0 = 0x206c460U;
    u32 value1 = *(const u32 *)(value0);
    u32 value2 = *(const unsigned char *)((value1 + 0x10U));
    u32 value3 = (value2) & (~(0x1U));
    u32 value4 = (value3) | (0x1U);
    *(unsigned char *)((value1 + 0x10U)) = value4;
    return value4;
}
