typedef unsigned int u32;
u32 func_ov029_020baa24(u32 argument0, u32 argument1, u32 argument2, u32 argument3) {
    u32 value0 = 0x20baba0U;
    u32 value1 = *(const u32 *)(value0);
    u32 value2 = *(const unsigned short *)((value1 + 0x6U));
    u32 value3 = (value2) | (0x4000U);
    *(unsigned short *)((value1 + 0x6U)) = value3;
    return value3;
}
