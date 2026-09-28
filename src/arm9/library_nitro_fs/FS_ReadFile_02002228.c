extern void *FSi_ReadFileCore();

void *FS_ReadFile_02002228(int a, void *b, void *c) {
    return FSi_ReadFileCore(a, b, c, 0);
}
