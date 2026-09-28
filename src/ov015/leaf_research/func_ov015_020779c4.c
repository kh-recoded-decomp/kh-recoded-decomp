typedef unsigned int u32;
u32 func_ov015_020779c4(u32 argument0, u32 argument1, u32 argument2, u32 argument3) {
    u32 value0 = 0x20812e0U;
    u32 value1 = *(const u32 *)(value0);
    u32 value2 = *(const u32 *)((value1 + 0xcU));
    *(u32 *)((value1 + 0x8U)) = value2;
    return value2;
}
