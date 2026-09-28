/* Independent reconstruction of a straight-line leaf from BK9E instructions.
 * Higher-level field and return meanings remain unclassified. */
typedef unsigned int u32;
u32 func_ov038_020bb65c(u32 argument0, u32 argument1, u32 argument2, u32 argument3) {
    u32 value0 = 0x20bd144U;
    u32 value1 = *(const u32 *)(value0);
    u32 value2 = (value1) + (0xd000U);
    u32 value3 = *(const u32 *)((value2 + 0xa0U));
    return value3;
}
