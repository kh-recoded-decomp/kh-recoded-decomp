extern int OS_DisableInterrupts(void);
extern void OS_RestoreInterrupts(int state);
extern void OSi_RescheduleThread(void);

void OS_WakeupThreadDirect_02002b60(char *thread) {
    int enabled = OS_DisableInterrupts();
    *(int *)(thread + 0x64) = 1;
    OSi_RescheduleThread();
    OS_RestoreInterrupts(enabled);
}
