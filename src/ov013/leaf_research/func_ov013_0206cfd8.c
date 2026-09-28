typedef unsigned int u32;
u32 func_ov013_0206cfd8(u32 argument0, u32 argument1, u32 argument2, u32 argument3) {
    u32 value0 = 0x4000000U;
    u32 value1 = *(const volatile u32 *)(value0);
    u32 value2 = (value1) & (~(0x1f00U));
    u32 value3 = (value2) | (0x1e00U);
    *(volatile u32 *)(value0) = value3;
    return value3;
}
