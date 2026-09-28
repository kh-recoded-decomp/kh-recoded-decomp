/* Independent reconstruction of a straight-line leaf from BK9E instructions.
 * Higher-level field and return meanings remain unclassified. */
typedef unsigned int u32;
u32 func_ov001_02075248(u32 argument0, u32 argument1, u32 argument2, u32 argument3) {
    u32 value0 = 0x20a04acU;
    u32 value1 = *(const u32 *)(value0);
    u32 value2 = 0x18U;
    u32 value3 = (argument0) * (value2);
    u32 value4 = (value1) + (value3);
    u32 value5 = *(const u32 *)((value4 + 0x7cU));
    return value5;
}
