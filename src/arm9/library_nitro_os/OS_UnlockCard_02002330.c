extern void *FS_ReadFile_02002228(int a, void *b, void *c);
extern void OSi_FreeCardBus(void);

void *OS_UnlockCard_02002330(unsigned short lockId) {
    return FS_ReadFile_02002228(lockId, (void *)0x02ffffe0, (void *)OSi_FreeCardBus);
}
