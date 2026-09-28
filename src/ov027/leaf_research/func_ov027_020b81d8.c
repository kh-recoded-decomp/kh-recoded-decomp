/* Independent reconstruction of a straight-line leaf from BK9E instructions.
 * Higher-level field and return meanings remain unclassified. */
typedef unsigned int u32;
u32 func_ov027_020b81d8(u32 argument0, u32 argument1, u32 argument2, u32 argument3) {
    *(unsigned short *)((argument1 + 0x2U)) = argument2;
    return argument0;
}
