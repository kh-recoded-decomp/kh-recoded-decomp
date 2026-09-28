/* Independent reconstruction of a straight-line leaf from BK9E instructions.
 * Higher-level field and return meanings remain unclassified. */
typedef unsigned int u32;
u32 func_ov059_020cac1c(u32 argument0, u32 argument1, u32 argument2, u32 argument3) {
    u32 value0 = 0xfffff000U;
    *(u32 *)(argument0) = value0;
    u32 value2 = 0x861U;
    u32 value3 = (argument1) * (value2);
    u32 value4 = 0x3244U;
    u32 value5 = (value3) - (value4);
    *(u32 *)((argument0 + 0x4U)) = value5;
    return argument0;
}
