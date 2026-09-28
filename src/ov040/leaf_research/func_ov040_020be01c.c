/* Independent reconstruction of a straight-line leaf from BK9E instructions.
 * Higher-level field and return meanings remain unclassified. */
typedef unsigned int u32;
u32 func_ov040_020be01c(u32 argument0, u32 argument1, u32 argument2, u32 argument3) {
    u32 value0 = 0x20be264U;
    u32 value1 = *(const u32 *)(value0);
    u32 value2 = *(const u32 *)((value1 + 0x8U));
    u32 value3 = *(const u32 *)((value2 + 0xcU));
    u32 value4 = (value3) + (0x8U);
    return value4;
}
