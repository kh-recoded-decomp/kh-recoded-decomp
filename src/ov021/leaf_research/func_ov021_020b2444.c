/* Independent reconstruction of a straight-line leaf from BK9E instructions.
 * Higher-level field and return meanings remain unclassified. */
typedef unsigned int u32;
u32 func_ov021_020b2444(u32 argument0, u32 argument1, u32 argument2, u32 argument3) {
    u32 value0 = *(const u32 *)((argument1 + 0x4U));
    *(u32 *)((argument0 + 0x24U)) = value0;
    u32 value2 = 0x7U;
    return value2;
}
