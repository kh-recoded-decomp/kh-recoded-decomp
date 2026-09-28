extern int data_020bea84[];
extern char data_020be8d0[];

void func_ov039_020bd054(int arg0)
{
    int index = data_020bea84[1];

    if (index != -1) {
        ((void (*)(int))*(int *)(*(char **)(data_020be8d0 + index * 8) + 8))(arg0);
    }
}
