/* Independent reconstruction of a straight-line leaf from BK9E instructions.
 * Higher-level field and return meanings remain unclassified. */
typedef unsigned int u32;
u32 func_ov049_020c3598(u32 argument0, u32 argument1, u32 argument2, u32 argument3) {
    u32 value0 = 0x5aU;
    u32 value1 = (value0) << 12;
    *(u32 *)((argument0 + 0x8U)) = value1;
    u32 value3 = 0x666U;
    *(u32 *)((argument0 + 0xcU)) = value3;
    *(u32 *)((argument0 + 0x10U)) = value3;
    u32 value6 = 0x0U;
    *(u32 *)((argument0 + 0x14U)) = value6;
    u32 value8 = 0x5U;
    u32 value9 = (value8) << 14;
    *(u32 *)((argument0 + 0x4U)) = value9;
    return argument0;
}
