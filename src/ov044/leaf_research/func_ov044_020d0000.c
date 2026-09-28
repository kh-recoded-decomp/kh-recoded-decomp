typedef unsigned int u32;
u32 func_ov044_020d0000(u32 argument0, u32 argument1, u32 argument2, u32 argument3) {
    u32 value0 = 0x1922U;
    *(u32 *)(argument0) = value0;
    u32 value2 = 0x666U;
    *(u32 *)((argument0 + 0x4U)) = value2;
    *(u32 *)((argument0 + 0x8U)) = value2;
    u32 value5 = 0x0U;
    *(u32 *)((argument0 + 0xcU)) = value5;
    u32 value7 = 0x5U;
    u32 value8 = (value7) << 14;
    *(u32 *)((argument0 + 0x10U)) = value8;
    return argument0;
}
