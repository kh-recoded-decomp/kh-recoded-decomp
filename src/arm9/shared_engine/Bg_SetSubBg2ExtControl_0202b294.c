extern void SetSubEngineGraphicsModeFromTable(void *ptr);
extern char data_020556a4;
extern int data_0205a920;

void Bg_SetSubBg2ExtControl_0202b294(int arg0, int arg1, int arg2) {
    volatile unsigned short *reg_bg2cnt_b = (volatile unsigned short *)0x0400100c;
    int arg3;

    SetSubEngineGraphicsModeFromTable(&data_020556a4);
    arg3 = data_0205a920;
    *reg_bg2cnt_b = (*reg_bg2cnt_b & 0x43) | (arg0 << 14) | (arg2 << 2) | (arg1 << 8) | (arg3 << 13);
}
