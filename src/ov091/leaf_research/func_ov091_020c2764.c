typedef unsigned int u32;
u32 func_ov091_020c2764(u32 argument0, u32 argument1, u32 argument2, u32 argument3) {
    u32 value0 = *(const u32 *)((argument0 + 0x4U));
    u32 value1 = ~(argument1);
    u32 value2 = (value0) & (value1);
    *(u32 *)((argument0 + 0x4U)) = value2;
    return argument0;
}
