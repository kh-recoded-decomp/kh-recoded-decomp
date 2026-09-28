extern int OSi_DoTryLockByWord_02002238(unsigned short id, char *lock, void (*onLock)(void), int fiq);
extern void OSi_AllocateCartridgeBus(void);

int OS_TryLockCartridge_020022e0(unsigned short id) {
    return OSi_DoTryLockByWord_02002238(id, (char *)0x02ffffe8, OSi_AllocateCartridgeBus, 1);
}
