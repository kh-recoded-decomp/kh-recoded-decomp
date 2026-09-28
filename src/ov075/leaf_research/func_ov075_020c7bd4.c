/* Independent reconstruction of a straight-line leaf from BK9E instructions.
 * Higher-level field and return meanings remain unclassified. */
typedef unsigned int u32;
u32 func_ov075_020c7bd4(u32 argument0, u32 argument1, u32 argument2, u32 argument3) {
    u32 value0 = (argument0) ^ (((u32)((int)(argument0) >> 31)));
    u32 value1 = (value0) - (((u32)((int)(argument0) >> 31)));
    return value1;
}
