typedef unsigned int u32;
u32 func_ov001_0206b948(u32 argument0, u32 argument1, u32 argument2, u32 argument3) {
    u32 value0 = 0x1U;
    *(u32 *)(argument0) = value0;
    *(unsigned short *)((argument0 + 0x4U)) = argument1;
    *(unsigned short *)((argument0 + 0x6U)) = argument2;
    return argument0;
}
