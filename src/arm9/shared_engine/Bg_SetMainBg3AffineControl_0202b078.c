extern void DispMode_LookupWordAndDispatch(void *ptr);
extern char data_02055664;
extern int data_0205a920;

void Bg_SetMainBg3AffineControl_0202b078(int arg0, int arg1, int arg2) {
    volatile unsigned short *reg_bg3cnt = (volatile unsigned short *)0x0400000e;
    int arg3;

    DispMode_LookupWordAndDispatch(&data_02055664);
    arg3 = data_0205a920;
    *reg_bg3cnt = (*reg_bg3cnt & 0x43) | (arg0 << 14) | (arg1 << 8) | (arg2 << 2) | (arg3 << 13);
}
