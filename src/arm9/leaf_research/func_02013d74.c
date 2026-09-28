/* Independent reconstruction of a straight-line leaf from BK9E instructions.
 * Higher-level field and return meanings remain unclassified. */
typedef unsigned int u32;
u32 func_02013d74(u32 argument0, u32 argument1, u32 argument2, u32 argument3) {
    u32 value0 = 0x205a8c4U;
    u32 value1 = 0x0U;
    *(u32 *)(value0) = value1;
    u32 value3 = *(const u32 *)((value0 + 0x8U));
    *(u32 *)((value0 + 0x4U)) = value3;
    return value0;
}
