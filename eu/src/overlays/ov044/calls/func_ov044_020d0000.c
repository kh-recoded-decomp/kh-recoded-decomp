typedef unsigned int u32;
u32 func_ov044_020d0000(u32 argument0, u32 argument1, u32 argument2, u32 argument3) {
    u32 value0 = 0x1922U;
    *(u32 *)(argument0) = value0;
    u32 value2 = 0xaeU;
    u32 value3 = (value2) << 2;
    *(u32 *)((argument0 + 0x4U)) = value3;
    u32 value5 = (value3) + (0x7bU);
    *(u32 *)((argument0 + 0x8U)) = value5;
    u32 value7 = 0x0U;
    *(u32 *)((argument0 + 0xcU)) = value7;
    u32 value9 = 0xaU;
    u32 value10 = (value9) << 12;
    *(u32 *)((argument0 + 0x10U)) = value10;
    return argument0;
}
