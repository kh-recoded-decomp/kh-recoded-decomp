typedef unsigned int u32;
u32 func_ov013_0207434c(u32 argument0, u32 argument1, u32 argument2, u32 argument3) {
    u32 value0 = 0x2074ce0U;
    u32 value1 = *(const u32 *)(value0);
    u32 value2 = (value1) + (0xd000U);
    u32 value3 = *(const unsigned char *)((value2 + 0x259U));
    u32 value4 = (value3) | (0x2U);
    *(unsigned char *)((value2 + 0x259U)) = value4;
    return value2;
}
