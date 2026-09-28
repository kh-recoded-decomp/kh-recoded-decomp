/* Independent reconstruction of a straight-line leaf from BK9E instructions.
 * Higher-level field and return meanings remain unclassified. */
typedef unsigned int u32;
u32 func_ov049_020c357c(u32 argument0, u32 argument1, u32 argument2, u32 argument3) {
    u32 value0 = 0x5aU;
    u32 value1 = (value0) << 12;
    *(u32 *)((argument0 + 0x8U)) = value1;
    u32 value3 = 0xaeU;
    u32 value4 = (value3) << 2;
    *(u32 *)((argument0 + 0xcU)) = value4;
    u32 value6 = (value4) + (0x7bU);
    *(u32 *)((argument0 + 0x10U)) = value6;
    u32 value8 = 0x0U;
    *(u32 *)((argument0 + 0x14U)) = value8;
    u32 value10 = 0xaU;
    u32 value11 = (value10) << 12;
    *(u32 *)((argument0 + 0x4U)) = value11;
    return argument0;
}
