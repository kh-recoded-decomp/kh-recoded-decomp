typedef unsigned int u32;
u32 func_ov001_0208f258(u32 argument0, u32 argument1, u32 argument2, u32 argument3) {
    u32 value0 = *(const u32 *)((argument0 + 0xcU));
    u32 value1 = *(const unsigned short *)((argument0 + 0x10U));
    u32 value2 = (argument1) - (0x1U);
    u32 value3 = (value2) << 16;
    u32 value4 = (value3) >> 16;
    u32 value5 = (value1) * (value4);
    u32 value6 = (value0) + (value5);
    return value6;
}
