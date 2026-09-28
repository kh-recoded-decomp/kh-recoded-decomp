extern int data_020bea84[];
extern char data_020be930[];

void func_ov039_020bcf20(int arg0)
{
    int index = data_020bea84[0];

    if (index != -1) {
        ((void (*)(int))*(int *)(*(char **)(data_020be930 + index * 8) + 8))(arg0);
    }
}
