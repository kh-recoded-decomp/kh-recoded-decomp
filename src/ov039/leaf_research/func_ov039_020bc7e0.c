typedef unsigned int u32;
u32 func_ov039_020bc7e0(u32 argument0, u32 argument1, u32 argument2, u32 argument3) {
    u32 value0 = 0x20bea00U;
    u32 value1 = *(const u32 *)(value0);
    u32 value2 = (value1) + (0xc000U);
    *(u32 *)((value2 + 0xa80U)) = argument0;
    return argument0;
}
