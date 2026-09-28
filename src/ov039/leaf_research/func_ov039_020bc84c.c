/* Independent reconstruction of a straight-line leaf from BK9E instructions.
 * Higher-level field and return meanings remain unclassified. */
typedef unsigned int u32;
u32 func_ov039_020bc84c(u32 argument0, u32 argument1, u32 argument2, u32 argument3) {
    u32 value0 = 0x20bea00U;
    u32 value1 = *(const u32 *)(value0);
    u32 value2 = (value1) + (0xc000U);
    u32 value3 = *(const u32 *)((value2 + 0xad4U));
    u32 value4 = (value3) - (0x1U);
    u32 value5 = (value1) + (((value4) << 2));
    u32 value6 = (value5) + (0xc000U);
    u32 value7 = *(const u32 *)((value6 + 0xad8U));
    return value7;
}
