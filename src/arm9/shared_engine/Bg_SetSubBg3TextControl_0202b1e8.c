extern void SetSubEngineGraphicsModeFromTable(void *ptr);
extern char data_02055684;

void Bg_SetSubBg3TextControl_0202b1e8(int arg0, int arg1, int arg2, int arg3) {
    volatile unsigned short *reg_bg3cnt_b = (volatile unsigned short *)0x0400100e;

    SetSubEngineGraphicsModeFromTable(&data_02055684);
    *reg_bg3cnt_b = (*reg_bg3cnt_b & 0x43) | (arg0 << 14) | (arg1 << 7) | (arg2 << 8) | (arg3 << 2);
}
