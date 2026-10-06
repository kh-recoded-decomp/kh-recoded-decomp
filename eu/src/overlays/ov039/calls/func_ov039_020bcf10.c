extern int data_ov039_020beaa4[];
extern char data_ov039_020be950[];

void func_ov039_020bcf10(int arg0)
{
    int index = data_ov039_020beaa4[0];

    if (index != -1) {
        ((void (*)(int))*(int *)(*(char **)(data_ov039_020be950 + index * 8) + 4))(arg0);
    }
}
