extern int Ov105_WmInitCore(int a0, int a1, int a2);
extern int data_020597fc;

int WmInit_02010d64(int a0, int a1) {
    int result = Ov105_WmInitCore(a0, a1, 0xf00);
    if (result != 0) {
        return result;
    }
    *(unsigned short *)(*(char **)((char *)&data_020597fc + 4) + 0x16) = 0;
    return result;
}
