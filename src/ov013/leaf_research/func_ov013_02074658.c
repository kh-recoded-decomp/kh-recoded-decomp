typedef unsigned int u32;
u32 func_ov013_02074658(u32 argument0, u32 argument1, u32 argument2, u32 argument3) {
    u32 value0 = 0x2074ce0U;
    u32 value1 = *(const u32 *)(value0);
    u32 value2 = *(const unsigned char *)((value1 + 0x99U));
    u32 value3 = (value2) | (0x20U);
    *(unsigned char *)((value1 + 0x99U)) = value3;
    return value3;
}
