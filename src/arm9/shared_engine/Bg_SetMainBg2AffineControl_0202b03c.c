extern void DispMode_LookupWordAndDispatch(void *ptr);
extern char data_020556c4;
extern int data_0205a920;

void Bg_SetMainBg2AffineControl_0202b03c(int arg0, int arg1, int arg2) {
    volatile unsigned short *reg_bg2cnt = (volatile unsigned short *)0x0400000c;
    int arg3;

    DispMode_LookupWordAndDispatch(&data_020556c4);
    arg3 = data_0205a920;
    *reg_bg2cnt = (*reg_bg2cnt & 0x43) | (arg0 << 14) | (arg1 << 8) | (arg2 << 2) | (arg3 << 13);
}
