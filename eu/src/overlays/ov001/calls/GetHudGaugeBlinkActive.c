extern int data_ov001_020a04cc;

int GetHudGaugeBlinkActive(int arg0) {
    return *(int *)(*(int *)&data_ov001_020a04cc + arg0 * 0x18 + 0x7c);
}
