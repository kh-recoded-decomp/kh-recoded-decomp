typedef unsigned int u32;
u32 func_ov031_020bc710(u32 argument0, u32 argument1, u32 argument2, u32 argument3) {
    u32 value0 = 0x20bc800U;
    u32 value1 = *(const u32 *)(value0);
    u32 value2 = (value1) + (0x5cU);
    *(unsigned short *)(value2) = argument0;
    return argument0;
}
