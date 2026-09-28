extern void MI_WaitDma(int ch);
extern void GX_SetBankForSubOBJExtPltt(int mask);
extern int data_02055c1c[];
extern int data_02056f0c[];

void GXS_EndLoadOBJExtPltt_02007fbc(void) {
    if (data_02055c1c[0] != -1) {
        MI_WaitDma(data_02055c1c[0]);
    }
    GX_SetBankForSubOBJExtPltt(data_02056f0c[6]);
    data_02056f0c[6] = 0;
}
