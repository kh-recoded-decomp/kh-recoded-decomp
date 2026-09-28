typedef unsigned int u32;
u32 func_ov004_02062250(u32 argument0, u32 argument1, u32 argument2, u32 argument3) {
    u32 value0 = 0x4001050U;
    u32 value1 = 0x0U;
    *(volatile unsigned short *)(value0) = value1;
    return value0;
}
