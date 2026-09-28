/* Independent reconstruction of a straight-line leaf from BK9E instructions.
 * Higher-level field and return meanings remain unclassified. */
typedef unsigned int u32;
u32 func_ov001_0207e07c(u32 argument0, u32 argument1, u32 argument2, u32 argument3) {
    u32 value0 = 0x20a04d0U;
    u32 value1 = *(const u32 *)(value0);
    u32 value2 = 0x1U;
    u32 value3 = *(const u32 *)((value1 + 0x28U));
    u32 value4 = (value3) & (~(value2));
    u32 value5 = 0x1U;
    u32 value6 = (value5) | (value4);
    *(u32 *)((value1 + 0x28U)) = value6;
    return value6;
}
