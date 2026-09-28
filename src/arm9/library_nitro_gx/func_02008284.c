extern void MI_WaitDma(int ch);
extern void GX_BeginLoadOBJExtPltt(int mask);
extern int data_02055c1c[];
extern int data_02056f28[];

void GX_EndLoadTexPltt_02008284(void) {
    if (data_02055c1c[0] != -1) {
        MI_WaitDma(data_02055c1c[0]);
    }
    GX_BeginLoadOBJExtPltt(data_02056f28[3]);
    data_02056f28[3] = 0;
    data_02056f28[2] = 0;
}
