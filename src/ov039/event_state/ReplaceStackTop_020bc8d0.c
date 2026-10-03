extern int data_ov039_020bea00;

void ReplaceStackTop_020bc8d0(int value)
{
    int base = data_ov039_020bea00;
    int *count = (int *)(base + 0xcad4);
    int index = (*count)--;

    *(int *)(base + index * 4 + 0xcad8) = 0;
    *(int *)(base + *count * 4 + 0xcad8) = value;
}
