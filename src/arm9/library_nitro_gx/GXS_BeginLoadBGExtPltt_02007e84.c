extern int GX_ResetBankForSubBGExtPltt(void);
extern int data_02056f0c[];

void GXS_BeginLoadBGExtPltt_02007e84(void) {
    data_02056f0c[0] = GX_ResetBankForSubBGExtPltt();
}
