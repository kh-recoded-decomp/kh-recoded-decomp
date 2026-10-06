extern void WriteSessionPackedBits(void *dest, unsigned char val, unsigned int size);

void func_ov001_020645dc(void *dest)
{
    WriteSessionPackedBits(dest, 1, 1);
}
