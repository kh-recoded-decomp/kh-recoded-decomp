/* Independent reconstruction of a straight-line leaf from BK9E instructions.
 * Higher-level field and return meanings remain unclassified. */
typedef unsigned int u32;
u32 func_ov001_020870bc(u32 argument0, u32 argument1, u32 argument2, u32 argument3) {
    u32 value0 = 0x20a04dcU;
    u32 value1 = *(const u32 *)(value0);
    u32 value2 = *(const unsigned char *)((value1 + 0x5U));
    u32 value3 = 0x11U;
    u32 value4 = (value3) & (value2);
    return value4;
}
