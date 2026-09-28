extern void WaitByLoop(unsigned count);
extern int OSi_DoTryLockByWord(unsigned short id, char *lock, void (*onLock)(void), int fiq);

int OSi_DoLockByWord_02002158(unsigned short id, char *lock, void (*onLock)(void), int fiq) {
    int prev = OSi_DoTryLockByWord(id, lock, onLock, fiq);

    while (prev > 0) {
        WaitByLoop(0x400);
        prev = OSi_DoTryLockByWord(id, lock, onLock, fiq);
    }
    return prev;
}
