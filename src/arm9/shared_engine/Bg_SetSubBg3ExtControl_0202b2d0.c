extern void SetSubEngineGraphicsModeFromTable(void *ptr);
extern char data_02055624;
extern int data_0205a920;

void Bg_SetSubBg3ExtControl_0202b2d0(int arg0, int arg1, int arg2) {
    volatile unsigned short *reg_bg3cnt_b = (volatile unsigned short *)0x0400100e;
    int arg3;

    SetSubEngineGraphicsModeFromTable(&data_02055624);
    arg3 = data_0205a920;
    *reg_bg3cnt_b = (*reg_bg3cnt_b & 0x43) | (arg0 << 14) | (arg2 << 2) | (arg1 << 8) | (arg3 << 13);
}
