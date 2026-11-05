extern void SetBrightnessAndSyncMain(void);
extern void SetSecondaryBrightness(int value);
extern void OS_WaitVBlankIntr(void);

void SetTitleBrightnessAndMaybeWaitVBlank(int value, int waitVBlank)
{
    SetBrightnessAndSyncMain();
    SetSecondaryBrightness(value);
    if (waitVBlank == 0) {
        return;
    }
    OS_WaitVBlankIntr();
}
