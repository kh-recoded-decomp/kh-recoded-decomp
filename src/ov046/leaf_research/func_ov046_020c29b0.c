/* Independent reconstruction of a straight-line leaf from BK9E instructions.
 * Higher-level field and return meanings remain unclassified. */
typedef unsigned int u32;
u32 func_ov046_020c29b0(u32 argument0, u32 argument1, u32 argument2, u32 argument3) {
    u32 value0 = 0x20c34e0U;
    u32 value1 = *(const u32 *)(value0);
    u32 value2 = (value1) + (0xf4U);
    *(u32 *)(value2) = argument0;
    return argument0;
}
