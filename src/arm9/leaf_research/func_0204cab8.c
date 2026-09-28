typedef unsigned int u32;
u32 func_0204cab8(u32 argument0, u32 argument1, u32 argument2, u32 argument3) {
    u32 value0 = 0x206084cU;
    u32 value1 = 0xb4738U;
    u32 value2 = *(const u32 *)(value0);
    u32 value3 = 0x0U;
    u32 value4 = (value2) + (value1);
    *(unsigned short *)((value4 + 0x80U)) = value3;
    *(unsigned short *)((value4 + 0x82U)) = value3;
    *(unsigned char *)((value4 + 0x84U)) = value3;
    return value4;
}
