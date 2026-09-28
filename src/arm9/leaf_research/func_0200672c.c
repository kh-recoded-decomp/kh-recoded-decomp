typedef unsigned int u32;
u32 func_0200672c(u32 argument0, u32 argument1, u32 argument2, u32 argument3) {
    u32 value0 = 0x4001000U;
    u32 value1 = *(const u32 *)(value0);
    u32 value2 = (value1) & (~(0x7U));
    u32 value3 = (value2) | (argument0);
    *(u32 *)(value0) = value3;
    return value3;
}
