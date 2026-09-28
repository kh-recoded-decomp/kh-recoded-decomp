typedef unsigned int u32;
u32 func_ov001_020925bc(u32 argument0, u32 argument1, u32 argument2, u32 argument3) {
    u32 value0 = *(const unsigned short *)((argument0 + 0x6U));
    *(u32 *)(argument0) = argument1;
    u32 value2 = 0x4U;
    u32 value3 = (value2) | (value0);
    *(unsigned short *)((argument0 + 0x6U)) = value3;
    return argument0;
}
