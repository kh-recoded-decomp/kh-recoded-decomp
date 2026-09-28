extern void MI_WaitDma(int ch);
extern void GX_SetBankForOBJExtPltt(int mask);
extern int data_02055c1c[];
extern int data_02056f0c[];

void GX_EndLoadOBJExtPltt_02007e48(void) {
    if (data_02055c1c[0] != -1) {
        MI_WaitDma(data_02055c1c[0]);
    }
    GX_SetBankForOBJExtPltt(data_02056f0c[2]);
    data_02056f0c[2] = 0;
    data_02056f0c[1] = 0;
}
