extern void OS_EnableInterrupts(void);
extern void OS_Halt(void);

void OSi_IdleThreadProc_02004d20(void) {
    OS_EnableInterrupts();
    for (;;) {
        OS_Halt();
    }
}
