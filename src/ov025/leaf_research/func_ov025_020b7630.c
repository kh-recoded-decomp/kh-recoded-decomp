/* Independent reconstruction of a straight-line leaf from BK9E instructions.
 * Higher-level field and return meanings remain unclassified. */
typedef unsigned int u32;
u32 func_ov025_020b7630(u32 argument0, u32 argument1, u32 argument2, u32 argument3) {
    u32 value0 = (argument1) << 2;
    u32 value1 = (argument0) + (value0);
    u32 value2 = *(const u32 *)((value1 + 0x70U));
    u32 value3 = *(const unsigned short *)((value2 + 0x4U));
    return value3;
}
