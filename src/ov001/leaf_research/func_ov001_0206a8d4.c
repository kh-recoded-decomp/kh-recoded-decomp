/* Independent reconstruction of a straight-line leaf from BK9E instructions.
 * Higher-level field and return meanings remain unclassified. */
typedef unsigned int u32;
u32 func_ov001_0206a8d4(u32 argument0, u32 argument1, u32 argument2, u32 argument3) {
    u32 value0 = 0x20a0480U;
    u32 value1 = *(const u32 *)(value0);
    u32 value2 = (value1) + (0x0U);
    u32 value3 = (value2) + (0x66U);
    u32 value4 = *(const unsigned char *)(value3);
    u32 value5 = 0x1U;
    u32 value6 = (value1) + (0x66U);
    u32 value7 = (value4) & (~(value5));
    u32 value8 = 0x1U;
    u32 value9 = (value8) | (value7);
    *(unsigned char *)(value6) = value9;
    return value9;
}
