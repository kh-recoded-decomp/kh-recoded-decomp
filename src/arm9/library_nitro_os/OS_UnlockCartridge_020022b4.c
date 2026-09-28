extern int OSi_DoUnlockByWord_020021b4(unsigned short id, char *lock, void (*onUnlock)(void), int fiq);
extern void OSi_FreeCartridgeBus(void);

int OS_UnlockCartridge_020022b4(unsigned short id) {
    return OSi_DoUnlockByWord_020021b4(id, (char *)0x02ffffe8, OSi_FreeCartridgeBus, 1);
}
