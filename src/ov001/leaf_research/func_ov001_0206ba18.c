/* Independent reconstruction of a straight-line leaf from BK9E instructions.
 * Higher-level field and return meanings remain unclassified. */
typedef unsigned int u32;
u32 func_ov001_0206ba18(u32 argument0, u32 argument1, u32 argument2, u32 argument3) {
    u32 value0 = 0x7fffffffU;
    *(u32 *)(argument0) = value0;
    u32 value2 = 0x0U;
    u32 value3 = ~(value2);
    *(u32 *)((argument0 + 0x4U)) = value3;
    u32 value5 = 0x0U;
    *(u32 *)((argument0 + 0x8U)) = value5;
    return argument0;
}
