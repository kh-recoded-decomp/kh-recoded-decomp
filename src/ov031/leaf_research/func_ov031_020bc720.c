typedef unsigned int u32;
u32 func_ov031_020bc720(u32 argument0, u32 argument1, u32 argument2, u32 argument3) {
    u32 value0 = 0x20bc800U;
    u32 value1 = *(const u32 *)(value0);
    u32 value2 = *(const u32 *)((value1 + 0x44U));
    u32 value3 = *(const u32 *)((value1 + 0x50U));
    u32 value4 = 0x3cU;
    u32 value5 = (value2) * (value4);
    u32 value6 = (value3) + (value5);
    u32 value7 = *(const u32 *)((value6 + 0x14U));
    return value7;
}
