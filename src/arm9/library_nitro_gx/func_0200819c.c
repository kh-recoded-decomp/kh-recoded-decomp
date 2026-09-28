extern void MI_WaitDma(int ch);
extern void GX_SetBankForTex(int mask);
extern int data_02055c1c[];
extern int data_02056f28[];

void GX_EndLoadTex_0200819c(void) {
    if (data_02055c1c[0] != -1) {
        MI_WaitDma(data_02055c1c[0]);
    }
    GX_SetBankForTex(data_02056f28[5]);
    data_02056f28[7] = 0;
    data_02056f28[6] = 0;
    data_02056f28[1] = 0;
    data_02056f28[5] = 0;
}
