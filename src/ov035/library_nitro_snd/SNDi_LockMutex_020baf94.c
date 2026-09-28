extern void OS_LockMutex(void *p);
extern int data_00003700;

void SNDi_LockMutex_020baf94(void) {
    OS_LockMutex(&data_00003700);
}
