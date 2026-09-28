int func_ov022_020a9f58(const unsigned char *movieContext)
{
    int tableIndex = *(const int *)(movieContext + 0x90);
    const int *tableWords = (const int *)(movieContext + 0x88);
    return tableWords[tableIndex];
}
