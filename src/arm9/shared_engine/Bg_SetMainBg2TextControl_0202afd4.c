extern void DispMode_LookupWordAndDispatch(void *ptr);
extern char data_020556e4;

void Bg_SetMainBg2TextControl_0202afd4(int arg0, int arg1, int arg2, int arg3) {
    volatile unsigned short *reg_bg2cnt = (volatile unsigned short *)0x0400000c;

    DispMode_LookupWordAndDispatch(&data_020556e4);
    *reg_bg2cnt = (*reg_bg2cnt & 0x43) | (arg0 << 14) | (arg1 << 7) | (arg2 << 8) | (arg3 << 2);
}
