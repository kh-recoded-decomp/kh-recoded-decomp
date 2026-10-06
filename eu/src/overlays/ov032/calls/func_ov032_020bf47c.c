typedef unsigned int u32;
u32 func_ov032_020bf47c(u32 argument0, u32 argument1, u32 argument2, u32 argument3) {
    u32 value0 = (argument0) + (0xecU);
    u32 value1 = *(const u32 *)(value0);
    u32 value2 = *(const u32 *)((value1 + 0x8U));
    u32 value3 = (value2) << 18;
    u32 value4 = (value3) >> 31;
    return value4;
}
