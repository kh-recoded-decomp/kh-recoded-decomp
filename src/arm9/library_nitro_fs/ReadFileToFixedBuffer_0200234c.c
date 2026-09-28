extern void *FS_ReadFile_020022a4(int a, void *b, void *c);
extern void OSi_AllocateCardBus(void);

void *ReadFileToFixedBuffer_0200234c(int handle) {
    return FS_ReadFile_020022a4(handle, (void *)0x02ffffe0, (void *)OSi_AllocateCardBus);
}
