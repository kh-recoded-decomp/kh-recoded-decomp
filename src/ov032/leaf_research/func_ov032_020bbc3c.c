/* Independent reconstruction of a straight-line leaf from BK9E instructions.
 * Higher-level field and return meanings remain unclassified. */
typedef unsigned int u32;
u32 func_ov032_020bbc3c(u32 argument0, u32 argument1, u32 argument2, u32 argument3) {
    u32 value0 = *(const u32 *)((argument0 + 0x8U));
    u32 value1 = 0x3fffffU;
    u32 value2 = (value0) & (value1);
    u32 value3 = 0x5aU;
    u32 value4 = (value3) << 22;
    u32 value5 = (value2) | (value4);
    u32 value6 = 0xffff003fU;
    u32 value7 = (value6) & (value5);
    *(u32 *)((argument0 + 0x8U)) = value7;
    u32 value9 = 0x1U;
    u32 value10 = (value9) << 12;
    *(u32 *)((argument1 + 0x30U)) = value10;
    return value10;
}
