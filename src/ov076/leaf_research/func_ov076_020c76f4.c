typedef unsigned int u32;
u32 func_ov076_020c76f4(u32 argument0, u32 argument1, u32 argument2, u32 argument3) {
    u32 value0 = (argument0) + (0x7U);
    u32 value1 = (value0) << 12;
    u32 value2 = (value1) + (0x80U);
    *(u32 *)(argument2) = value2;
    u32 value4 = (argument1) + (0x8U);
    u32 value5 = 0xc0U;
    u32 value6 = (value5) - (value4);
    u32 value7 = (value6) << 12;
    *(u32 *)(argument3) = value7;
    return value7;
}
