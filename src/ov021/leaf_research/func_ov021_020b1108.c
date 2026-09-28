typedef unsigned int u32;
u32 func_ov021_020b1108(u32 argument0, u32 argument1, u32 argument2, u32 argument3) {
    u32 value0 = 0x10U;
    *(unsigned short *)((argument0 + 0x2cU)) = value0;
    u32 value2 = *(const u32 *)((argument0 + 0x38U));
    *(u32 *)((argument0 + 0x30U)) = value2;
    u32 value4 = 0x0U;
    return value4;
}
