extern void *FSi_ReadFileCore();

void *FS_ReadFile_020022a4(int a, void *b, void *c) {
    return FSi_ReadFileCore(a, b, c, 0);
}
