typedef unsigned int u32;
u32 func_020152d8(u32 argument0, u32 argument1, u32 argument2, u32 argument3) {
    u32 value0 = (argument0) + (((argument1) << 2));
    *(u32 *)((value0 + 0x8U)) = argument2;
    return value0;
}
