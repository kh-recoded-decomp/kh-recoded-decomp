/* Independent reconstruction of a straight-line leaf from BK9E instructions.
 * Higher-level field and return meanings remain unclassified. */
typedef unsigned int u32;
u32 func_02015274(u32 argument0, u32 argument1, u32 argument2, u32 argument3) {
    u32 value0 = 0x2U;
    *(u32 *)((argument0 + 0x20U)) = value0;
    *(u32 *)((argument0 + 0x28U)) = argument2;
    *(u32 *)((argument0 + 0x24U)) = argument1;
    *(unsigned short *)((argument0 + 0x2cU)) = argument3;
    return argument0;
}
