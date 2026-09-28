extern int LookupPairKey(void *ptr, unsigned short arg1, unsigned short arg2);
extern void (*data_020555c4[])(int value, int arg1, int arg2);
extern char data_02055594;

void Gfx_DispatchByPairKeyA_0202b344(int index, unsigned short *args, int arg1, int arg2) {
    int value = LookupPairKey(&data_02055594, args[0], args[1]);

    data_020555c4[index](value, arg1, arg2);
}
