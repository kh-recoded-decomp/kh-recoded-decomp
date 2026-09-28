/* Independent reconstruction of a straight-line leaf from BK9E instructions.
 * Higher-level field and return meanings remain unclassified. */
typedef unsigned int u32;
u32 func_02013f74(u32 argument0, u32 argument1, u32 argument2, u32 argument3) {
    u32 value0 = *(const unsigned short *)((argument0 + 0x8U));
    u32 value1 = *(const u32 *)(argument0);
    u32 value2 = (value1) + (((value0) << 4));
    return value2;
}
