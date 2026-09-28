/* Independent reconstruction of a straight-line leaf from BK9E instructions.
 * Higher-level field and return meanings remain unclassified. */
typedef unsigned int u32;
u32 func_ov001_02066ef8(u32 argument0, u32 argument1, u32 argument2, u32 argument3) {
    u32 value0 = 0x20a046cU;
    u32 value1 = *(const u32 *)(value0);
    u32 value2 = *(const u32 *)((value1 + 0x14U));
    u32 value3 = 0x24U;
    u32 value4 = (argument1) * (value3);
    u32 value5 = (value2) + (value4);
    u32 value6 = (value5) + (0x0U);
    u32 value7 = *(const unsigned char *)((argument0 + 0x1U));
    u32 value8 = (value6) + (0x20U);
    *(unsigned char *)(value8) = value7;
    u32 value10 = (value5) + (0x0U);
    u32 value11 = *(const unsigned char *)((argument0 + 0x2U));
    u32 value12 = (value10) + (0x21U);
    *(unsigned char *)(value12) = value11;
    u32 value14 = *(const unsigned short *)((argument0 + 0x4U));
    *(unsigned short *)((value5 + 0x22U)) = value14;
    *(u32 *)((value5 + 0x1cU)) = argument0;
    return argument0;
}
