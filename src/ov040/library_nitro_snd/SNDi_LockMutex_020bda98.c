extern void OS_LockMutex(void *p);
extern int data_00003724;

void SNDi_LockMutex_020bda98(void) {
    OS_LockMutex(&data_00003724);
}
