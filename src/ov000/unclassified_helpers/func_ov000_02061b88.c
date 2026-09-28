extern void func_02029e7c(void);
extern void func_02029ed0(int value);
extern void OS_WaitVBlankIntr_020049d0(void);

void func_ov000_02061b88(int value, int waitVBlank)
{
    func_02029e7c();
    func_02029ed0(value);
    if (waitVBlank == 0) {
        return;
    }
    OS_WaitVBlankIntr_020049d0();
}
