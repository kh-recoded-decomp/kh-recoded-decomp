extern void OS_LockMutex(void *p);
extern int data_00003722;

void SNDi_LockMutex_020bda88(void) {
    OS_LockMutex(&data_00003722);
}
