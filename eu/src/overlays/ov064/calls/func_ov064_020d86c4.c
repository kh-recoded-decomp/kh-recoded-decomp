typedef unsigned int u32;
u32 func_ov064_020d86c4(u32 argument0, u32 argument1, u32 argument2, u32 argument3) {
    u32 value0 = (argument1) + (0x0U);
    u32 value1 = 0x0U;
    u32 value2 = (value0) + (0x44U);
    *(unsigned char *)(value2) = value1;
    u32 value4 = (value1) - (0x1U);
    *(u32 *)((argument1 + 0x64U)) = value4;
    return value4;
}
