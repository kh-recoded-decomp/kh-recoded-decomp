extern int data_ov039_020bea00;

void PushStackEntry_020bc874(int value)
{
    int base = data_ov039_020bea00;
    int *count = (int *)(base + 0xcad4);
    int index = (*count)++;

    *(int *)(base + index * 4 + 0xcad8) = value;
}
