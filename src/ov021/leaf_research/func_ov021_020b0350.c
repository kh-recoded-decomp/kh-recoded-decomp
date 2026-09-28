typedef unsigned int u32;
u32 func_ov021_020b0350(u32 argument0, u32 argument1, u32 argument2, u32 argument3) {
    u32 value0 = *(const u32 *)((argument0 + 0x8U));
    u32 value1 = *(const u32 *)((argument0 + 0x18U));
    u32 value2 = *(const u32 *)((argument0 + 0x1cU));
    u32 value3 = (value1) + (value2);
    u32 value4 = (value0) + (value3);
    return value4;
}
