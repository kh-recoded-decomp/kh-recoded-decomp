typedef unsigned int u32;
u32 func_ov028_020bb17c(u32 argument0, u32 argument1, u32 argument2, u32 argument3) {
    u32 value0 = 0x20bb380U;
    u32 value1 = *(const u32 *)(value0);
    u32 value2 = *(const unsigned short *)((value1 + 0x6U));
    u32 value3 = (value2) & (0x60U);
    return value3;
}
