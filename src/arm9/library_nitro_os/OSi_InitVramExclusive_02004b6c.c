extern int data_02056ec8[];
extern unsigned short data_02056ecc[];

void OSi_InitVramExclusive_02004b6c(void) {
    int i = 0;
    int z = i;
    data_02056ec8[0] = z;
    do {
        data_02056ecc[i] = (unsigned short)z;
        i = i + 1;
    } while (i < 9);
}
