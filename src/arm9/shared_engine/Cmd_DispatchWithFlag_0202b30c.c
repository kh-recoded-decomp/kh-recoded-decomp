extern int LookupPairKey(void *ptr, unsigned short arg1, unsigned short arg2);
extern void (*const data_020555e4[])(int value, int flag, int arg1, int arg2);
extern char data_020555ac;

enum { FLAG_CLEAR = 0, FLAG_SET = 1 };

void Cmd_DispatchWithFlag_0202b30c(int index, unsigned short *args, int arg1, int arg2)
{
    int flag = args[2] == 0 ? FLAG_CLEAR : FLAG_SET;
    int value = LookupPairKey(&data_020555ac, args[0], args[1]);

    data_020555e4[index](value, flag, arg1, arg2);
}
