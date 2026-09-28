typedef unsigned int u32;
u32 func_ov021_020a7544(u32 argument0, u32 argument1, u32 argument2, u32 argument3) {
    u32 value0 = *(const unsigned short *)(argument0);
    u32 value1 = *(const unsigned short *)((argument0 + 0x4U));
    u32 value2 = (value0) + (value1);
    u32 value3 = (value2) << 16;
    u32 value4 = (value3) >> 16;
    return value4;
}
