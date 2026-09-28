/* Independent reconstruction of a straight-line leaf from BK9E instructions.
 * Higher-level field and return meanings remain unclassified. */
typedef unsigned int u32;
u32 func_02036874(u32 argument0, u32 argument1, u32 argument2, u32 argument3) {
    u32 value0 = 0x206083cU;
    u32 value1 = 0x0U;
    u32 value2 = *(const u32 *)(value0);
    u32 value3 = 0xff7fU;
    u32 value4 = (value2) + (((argument1) << 2));
    *(u32 *)((value4 + 0x20U)) = value1;
    u32 value6 = *(const unsigned short *)((argument0 + 0x8U));
    u32 value7 = (value6) & (value3);
    *(unsigned short *)((argument0 + 0x8U)) = value7;
    return argument0;
}
