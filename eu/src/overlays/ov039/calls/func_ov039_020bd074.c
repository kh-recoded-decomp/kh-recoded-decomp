extern int data_ov039_020beaa4[];
extern char data_ov039_020be8f0[];

void func_ov039_020bd074(int arg0)
{
    int index = data_ov039_020beaa4[1];

    if (index != -1) {
        ((void (*)(int))*(int *)(*(char **)(data_ov039_020be8f0 + index * 8) + 8))(arg0);
    }
}
