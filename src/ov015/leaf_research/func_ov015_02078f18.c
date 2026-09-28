/* Independent reconstruction of a straight-line leaf from BK9E instructions.
 * Higher-level field and return meanings remain unclassified. */
typedef unsigned int u32;
u32 func_ov015_02078f18(u32 argument0, u32 argument1, u32 argument2, u32 argument3) {
    u32 value0 = 0x400100cU;
    u32 value1 = *(const volatile unsigned short *)(value0);
    u32 value2 = (value1) & (0x43U);
    u32 value3 = (value2) | (0x94U);
    *(volatile unsigned short *)(value0) = value3;
    return value3;
}
