typedef unsigned int u32;
u32 func_ov015_020731bc(u32 argument0, u32 argument1, u32 argument2, u32 argument3) {
    u32 value0 = 0x207e964U;
    u32 value1 = 0xc8U;
    u32 value2 = *(const u32 *)(value0);
    *(unsigned short *)((value2 + 0x7cU)) = value1;
    return value2;
}
