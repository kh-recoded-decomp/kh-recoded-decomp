/* Independent reconstruction of a straight-line leaf from BK9E instructions.
 * Higher-level field and return meanings remain unclassified. */
typedef unsigned int u32;
u32 func_ov030_020babdc(u32 argument0, u32 argument1, u32 argument2, u32 argument3) {
    u32 value0 = 0x20bd000U;
    u32 value1 = *(const u32 *)(value0);
    u32 value2 = 0xfffdU;
    u32 value3 = *(const unsigned short *)((value1 + 0x6U));
    u32 value4 = (value2) & (value3);
    *(unsigned short *)((value1 + 0x6U)) = value4;
    return value4;
}
