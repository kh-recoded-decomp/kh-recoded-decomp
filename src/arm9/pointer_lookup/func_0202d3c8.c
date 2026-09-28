int func_0202d3c8(int *objectBase, int recordIndex)
{
    int *table = ((int **)(objectBase + recordIndex))[2];
    if (table != 0)
        return *table;
    return 0;
}
