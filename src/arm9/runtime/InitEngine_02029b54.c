extern void PXI_Init_020034c4(void);
extern void func_0200644c(void);
extern void func_0200d560(int priority);
extern void func_02006488(void);
extern void initialize_frame_timer_02003eec(void);
extern void RTC_Init_0200e428(void);
extern void func_0200903c(void);
extern void func_02009144(int a, int b);
extern void func_02006640(void);
extern void SetBrightnessAndSyncMain_02029e7c(int value);
extern void SetSecondaryBrightness_02029ed0(int value);
extern void *GfxQueue_Configure_02013fd0(int a, int b);
extern void InitVBlankInterrupt_020010cc(void);
extern unsigned int OS_EnableIrqMask(unsigned int mask);
extern void func_0202a040(int oldIme);
extern void ClearVideoMemory_0202993c(void);
extern void SetupDisplayRegs_020299f4(void);
extern void InitTouchPanel_020299c0(void);
extern void func_02029ad8(void);

extern int data_02055c1c;
extern int data_02060088;

void InitEngine_02029b54(void)
{
    volatile unsigned short *keypadReg = (volatile unsigned short *)0x04000304;
    volatile unsigned short *ime = (volatile unsigned short *)0x04000208;
    unsigned short oldIme;

    PXI_Init_020034c4();
    func_0200644c();
    func_0200d560(3);
    *keypadReg = (*keypadReg & ~0x20e) | 0x20e;
    data_02055c1c = 1;
    func_02006488();
    initialize_frame_timer_02003eec();
    RTC_Init_0200e428();
    func_0200903c();
    func_02009144(0x500, 0x2400);
    func_02006640();
    *(volatile unsigned int *)0x04001000 &= 0xfffeffff;
    SetBrightnessAndSyncMain_02029e7c(0x10);
    SetSecondaryBrightness_02029ed0(0x10);
    GfxQueue_Configure_02013fd0((int)&data_02060088, 0x30);
    InitVBlankInterrupt_020010cc();
    OS_EnableIrqMask(0x40000);
    oldIme = *ime;
    *ime = 1;
    func_0202a040(oldIme);
    ClearVideoMemory_0202993c();
    SetupDisplayRegs_020299f4();
    InitTouchPanel_020299c0();
    func_02029ad8();
}
