/* Independent reconstruction of a straight-line leaf from BK9E instructions.
 * Higher-level field and return meanings remain unclassified. */
typedef unsigned int u32;
u32 func_ov039_020bca18(u32 argument0, u32 argument1, u32 argument2, u32 argument3) {
    u32 value0 = 0x20bea00U;
    u32 value1 = *(const u32 *)(value0);
    u32 value2 = (value1) + (0xca00U);
    u32 value3 = *(const unsigned short *)((value2 + 0x48U));
    return value3;
}
