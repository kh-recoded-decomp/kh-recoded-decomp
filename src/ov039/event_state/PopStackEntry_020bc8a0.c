extern int data_ov039_020bea00;

void PopStackEntry_020bc8a0(void)
{
    int base = data_ov039_020bea00;
    int *count = (int *)(base + 0xcad4);
    int index = (*count)--;

    *(int *)(base + index * 4 + 0xcad8) = 0;
}
