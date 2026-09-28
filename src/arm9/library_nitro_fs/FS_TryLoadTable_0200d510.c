extern void *FS_LoadArchiveTables();
extern char data_02057b24;

void *FS_TryLoadTable_0200d510(void *mem, unsigned int size) {
    return FS_LoadArchiveTables(&data_02057b24, mem, size);
}
