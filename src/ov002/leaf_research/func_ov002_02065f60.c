typedef unsigned int u32;
u32 func_ov002_02065f60(u32 argument0, u32 argument1, u32 argument2, u32 argument3) {
    u32 value0 = 0x206c464U;
    u32 value1 = *(const u32 *)(value0);
    u32 value2 = *(const unsigned char *)((value1 + 0x22U));
    u32 value3 = (value2) | (0x10U);
    *(unsigned char *)((value1 + 0x22U)) = value3;
    return value3;
}
