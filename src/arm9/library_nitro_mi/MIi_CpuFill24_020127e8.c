extern void MI_CpuFill8(void *dest, unsigned char val, unsigned int size);

void MIi_CpuFill24_020127e8(void *dest)
{
    MI_CpuFill8(dest, 0, 0x24);
}
