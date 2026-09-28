typedef unsigned int u32;
u32 func_0202f4e8(u32 argument0, u32 argument1, u32 argument2, u32 argument3) {
    u32 value0 = *(const unsigned short *)(argument0);
    u32 value1 = 0xfffdU;
    u32 value2 = (value0) & (value1);
    *(unsigned short *)(argument0) = value2;
    return argument0;
}
