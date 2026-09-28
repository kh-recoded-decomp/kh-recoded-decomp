/* Independent reconstruction of a straight-line leaf from BK9E instructions.
 * Higher-level field and return meanings remain unclassified. */
typedef unsigned int u32;
u32 func_ov017_020a5dd0(u32 argument0, u32 argument1, u32 argument2, u32 argument3) {
    u32 value0 = (argument0) + (0x54U);
    u32 value1 = *(const unsigned short *)(value0);
    u32 value2 = 0x8U;
    u32 value3 = (value2) & (value1);
    return value3;
}
