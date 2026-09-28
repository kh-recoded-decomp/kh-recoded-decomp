/* Independent reconstruction of a straight-line leaf from BK9E instructions.
 * Higher-level field and return meanings remain unclassified. */
typedef unsigned int u32;
u32 func_ov013_02073234(u32 argument0, u32 argument1, u32 argument2, u32 argument3) {
    u32 value0 = 0x2074ce0U;
    u32 value1 = 0x0U;
    u32 value2 = *(const u32 *)(value0);
    *(u32 *)((value2 + 0x2bcU)) = value1;
    return value2;
}
