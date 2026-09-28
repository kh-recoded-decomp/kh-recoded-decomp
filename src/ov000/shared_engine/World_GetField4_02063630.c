extern int *data_02063a04;

int World_GetField4_02063630(void)
{
    if (data_02063a04 != 0) {
        return data_02063a04[1];
    }
    return 2;
}
