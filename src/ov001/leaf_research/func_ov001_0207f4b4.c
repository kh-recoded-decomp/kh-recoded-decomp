/* Independent reconstruction of a straight-line leaf from BK9E instructions.
 * Higher-level field and return meanings remain unclassified. */
typedef unsigned int u32;
u32 func_ov001_0207f4b4(u32 argument0, u32 argument1, u32 argument2, u32 argument3) {
    u32 value0 = *(const u32 *)((argument0 + 0x48U));
    u32 value1 = (argument0) + (0x44U);
    u32 value2 = *(const unsigned short *)(value1);
    u32 value3 = (value2) * (argument1);
    u32 value4 = (value0) + (value3);
    return value4;
}
