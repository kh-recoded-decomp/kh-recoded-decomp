/* Independent reconstruction of a straight-line leaf from BK9E instructions.
 * Higher-level field and return meanings remain unclassified. */
typedef unsigned int u32;
u32 func_02036828(u32 argument0, u32 argument1, u32 argument2, u32 argument3) {
    u32 value0 = 0x206083cU;
    u32 value1 = (argument1) & (0xffU);
    u32 value2 = *(const u32 *)(value0);
    u32 value3 = (value2) + (((argument0) << 2));
    u32 value4 = *(const u32 *)((value3 + 0x20U));
    u32 value5 = *(const unsigned char *)((value4 + 0xbU));
    u32 value6 = (value5) + (value1);
    *(unsigned char *)((value4 + 0xbU)) = value6;
    return value6;
}
