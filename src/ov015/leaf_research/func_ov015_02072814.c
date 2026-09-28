/* Independent reconstruction of a straight-line leaf from BK9E instructions.
 * Higher-level field and return meanings remain unclassified. */
typedef unsigned int u32;
u32 func_ov015_02072814(u32 argument0, u32 argument1, u32 argument2, u32 argument3) {
    u32 value0 = 0x207e960U;
    u32 value1 = *(const u32 *)(value0);
    u32 value2 = *(const unsigned char *)((value1 + 0xe2U));
    u32 value3 = (value2) | (0x8U);
    *(unsigned char *)((value1 + 0xe2U)) = value3;
    return value3;
}
