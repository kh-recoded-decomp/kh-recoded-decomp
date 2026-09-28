/* Independent reconstruction of a straight-line leaf from BK9E instructions.
 * Higher-level field and return meanings remain unclassified. */
typedef unsigned int u32;
u32 func_0204993c(u32 argument0, u32 argument1, u32 argument2, u32 argument3) {
    u32 value0 = *(const u32 *)(argument0);
    u32 value1 = *(const u32 *)(argument1);
    *(u32 *)(argument0) = value1;
    *(u32 *)(argument1) = value0;
    return argument0;
}
