extern void WriteSessionPackedBits(void *dest, unsigned char val, unsigned int size);

void SetSessionFlag(void *dest)
{
    WriteSessionPackedBits(dest, 1, 1);
}
