extern void DispMode_LookupWordAndDispatch(void *ptr);
extern char data_020556a4;
extern int data_0205a920;

void Bg_SetMainBg2ExtControl_0202b0b4(int arg0, int arg1, int arg2) {
    volatile unsigned short *reg_bg2cnt = (volatile unsigned short *)0x0400000c;
    int arg3;

    DispMode_LookupWordAndDispatch(&data_020556a4);
    arg3 = data_0205a920;
    *reg_bg2cnt = (*reg_bg2cnt & 0x43) | (arg0 << 14) | (arg2 << 2) | (arg1 << 8) | (arg3 << 13);
}
