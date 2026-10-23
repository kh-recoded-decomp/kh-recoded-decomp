extern void OS_UnlockCartridge_0x020022c8(int processor) __attribute__((long_call));

void OS_UnLockCartridge(int processor)
{
    OS_UnlockCartridge_0x020022c8(processor);
}
