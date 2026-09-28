extern int GX_ResetBankForSubOBJExtPltt(void);
extern int data_02056f0c[];

void GXS_BeginLoadOBJExtPltt_02007f3c(void) {
    data_02056f0c[6] = GX_ResetBankForSubOBJExtPltt();
}
