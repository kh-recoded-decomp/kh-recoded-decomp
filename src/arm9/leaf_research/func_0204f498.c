/* Independent reconstruction of a straight-line leaf from BK9E instructions.
 * Higher-level field and return meanings remain unclassified. */
typedef unsigned int u32;
u32 func_0204f498(u32 argument0, u32 argument1, u32 argument2, u32 argument3) {
    u32 value0 = (argument0) + (0x6000U);
    *(u32 *)((value0 + 0x1cU)) = argument1;
    return value0;
}
