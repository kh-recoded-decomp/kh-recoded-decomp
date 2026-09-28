typedef unsigned int u32;
u32 func_ov085_020c1420(u32 argument0, u32 argument1, u32 argument2, u32 argument3) {
    u32 value0 = *(const u32 *)(argument0);
    u32 value1 = *(const u32 *)((value0 + 0x8U));
    u32 value2 = *(const u32 *)((value1 + 0xcU));
    u32 value3 = *(const u32 *)(argument1);
    u32 value4 = *(const u32 *)((value3 + 0x8U));
    u32 value5 = *(const u32 *)((value4 + 0xcU));
    u32 value6 = (value2) - (value5);
    return value6;
}
