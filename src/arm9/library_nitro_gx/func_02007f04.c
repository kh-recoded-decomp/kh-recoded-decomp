extern void MI_WaitDma(int ch);
extern void GX_SetBankForSubBGExtPltt(int mask);
extern int data_02055c1c[];
extern int data_02056f0c[];

void GXS_EndLoadBGExtPltt_02007f04(void) {
    if (data_02055c1c[0] != -1) {
        MI_WaitDma(data_02055c1c[0]);
    }
    GX_SetBankForSubBGExtPltt(data_02056f0c[0]);
    data_02056f0c[0] = 0;
}
