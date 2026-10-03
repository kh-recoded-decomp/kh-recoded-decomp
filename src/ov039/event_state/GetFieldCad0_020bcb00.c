extern int data_ov039_020bea00;

int GetFieldCad0_020bcb00(void)
{
    int base = data_ov039_020bea00;

    if (base != 0) {
        return *(int *)(base + 0xcad0);
    }
    return 0;
}
