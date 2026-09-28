typedef unsigned int u32;
u32 func_02013f84(u32 argument0, u32 argument1, u32 argument2, u32 argument3) {
    u32 value0 = *(const unsigned short *)((argument0 + 0xaU));
    u32 value1 = *(const u32 *)(argument0);
    u32 value2 = (value1) + (((value0) << 4));
    return value2;
}
