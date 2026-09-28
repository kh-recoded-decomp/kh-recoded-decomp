/* Independent reconstruction of a straight-line leaf from BK9E instructions.
 * Higher-level field and return meanings remain unclassified. */
typedef unsigned int u32;
u32 func_ov001_0206dba0(u32 argument0, u32 argument1, u32 argument2, u32 argument3) {
    u32 value0 = 0x20a049cU;
    u32 value1 = (argument0) << 2;
    u32 value2 = *(const u32 *)(value0);
    u32 value3 = (value2) + (value1);
    u32 value4 = (value3) + (0xb8U);
    u32 value5 = *(const u32 *)(value4);
    return value5;
}
