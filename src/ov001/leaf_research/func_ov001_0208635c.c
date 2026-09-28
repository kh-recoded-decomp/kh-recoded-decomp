typedef unsigned int u32;
u32 func_ov001_0208635c(u32 argument0, u32 argument1, u32 argument2, u32 argument3) {
    u32 value0 = *(const u32 *)((argument0 + 0x40U));
    u32 value1 = *(const unsigned short *)((argument0 + 0x3cU));
    u32 value2 = (value1) * (argument1);
    u32 value3 = (value0) + (value2);
    return value3;
}
