extern void OS_LockMutex(void *p);
extern int data_02059804;

void SNDi_LockMutex_02011404(void) {
    OS_LockMutex(&data_02059804);
}
