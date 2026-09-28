typedef unsigned int u32;
u32 func_ov001_020680e4(u32 argument0, u32 argument1, u32 argument2, u32 argument3) {
    u32 value0 = 0x20a046cU;
    u32 value1 = (argument0) << 2;
    u32 value2 = *(const u32 *)(value0);
    u32 value3 = *(const u32 *)(value2);
    u32 value4 = (value3) + (value1);
    u32 value5 = *(const u32 *)((value4 + 0x8U));
    u32 value6 = *(const unsigned char *)((value5 + 0x19U));
    *(unsigned char *)((value5 + 0x19U)) = argument1;
    return value6;
}
