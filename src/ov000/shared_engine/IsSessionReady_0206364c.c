extern int *data_02063a04;
int IsSessionReady_0206364c(void)
{
    if (data_02063a04 != 0) {
        return data_02063a04[0];
    }
    return 0;
}
