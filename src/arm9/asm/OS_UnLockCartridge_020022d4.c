extern void OS_UnlockCartridge_0x020022c8_020022b4(int processor);

asm void OS_UnLockCartridge_020022d4(int processor)
{
    ldr r1, =OS_UnlockCartridge_0x020022c8_020022b4
    bx  r1
}
