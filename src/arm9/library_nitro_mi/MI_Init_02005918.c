extern void MI_SetWramBank(int bank);
extern void MI_StopDma(int ch);

void MI_Init_02005918(void) {
    MI_SetWramBank(3);
    MI_StopDma(0);
}
