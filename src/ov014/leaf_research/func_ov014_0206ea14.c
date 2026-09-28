typedef unsigned int u32;
u32 func_ov014_0206ea14(u32 argument0, u32 argument1, u32 argument2, u32 argument3) {
    u32 value0 = 0x206f9a0U;
    u32 value1 = 0x40U;
    u32 value2 = *(const u32 *)(value0);
    u32 value3 = (value2) + (0xc000U);
    *(u32 *)((value3 + 0xb4cU)) = value1;
    return value3;
}
