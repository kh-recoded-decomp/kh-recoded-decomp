extern int LookupPairKey(void *ptr, unsigned short arg1, unsigned short arg2);
extern void (*data_02055644[])(int value, int arg1, int arg2);
extern char data_0205557c;

void Gfx_DispatchByPairKeyA_0202b370(int index, unsigned short *args, int arg1, int arg2) {
    int value = LookupPairKey(&data_0205557c, args[0], args[1]);

    data_02055644[index](value, arg1, arg2);
}
