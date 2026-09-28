/* Independent reconstruction of a straight-line leaf from BK9E instructions.
 * Higher-level field and return meanings remain unclassified. */
typedef unsigned int u32;
u32 func_ov038_020ba6e0(u32 argument0, u32 argument1, u32 argument2, u32 argument3) {
    u32 value0 = 0x20bd140U;
    u32 value1 = *(const u32 *)(value0);
    u32 value2 = *(const unsigned short *)((value1 + 0x6U));
    u32 value3 = (value2) & (0x20U);
    return value3;
}
