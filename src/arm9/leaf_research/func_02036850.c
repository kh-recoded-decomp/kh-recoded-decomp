/* Independent reconstruction of a straight-line leaf from BK9E instructions.
 * Higher-level field and return meanings remain unclassified. */
typedef unsigned int u32;
u32 func_02036850(u32 argument0, u32 argument1, u32 argument2, u32 argument3) {
    u32 value0 = 0x206083cU;
    u32 value1 = *(const u32 *)(value0);
    u32 value2 = (value1) + (((argument1) << 2));
    *(u32 *)((value2 + 0x20U)) = argument0;
    u32 value4 = *(const unsigned short *)((argument0 + 0x8U));
    u32 value5 = (value4) | (0x80U);
    *(unsigned short *)((argument0 + 0x8U)) = value5;
    return argument0;
}
