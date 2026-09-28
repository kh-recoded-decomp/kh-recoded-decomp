extern int func_02008d38(void);
extern int data_02056f28[];
extern unsigned short data_020528f4[];

void GX_BeginLoadTexPltt_020081e0(void) {
    int mask = func_02008d38();
    data_02056f28[3] = mask;
    data_02056f28[2] = data_020528f4[mask >> 4] << 12;
}
