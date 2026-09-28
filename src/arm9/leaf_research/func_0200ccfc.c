typedef unsigned int u32;
u32 func_0200ccfc(u32 argument0, u32 argument1, u32 argument2, u32 argument3) {
    u32 value0 = *(const u32 *)((argument1 + 0x4U));
    u32 value1 = 0x0U;
    u32 value2 = *(const u32 *)((value0 + 0x8U));
    u32 value3 = *(const u32 *)((value0 + 0x4U));
    u32 value4 = (value2) - (value3);
    *(u32 *)(argument2) = value4;
    return value1;
}
