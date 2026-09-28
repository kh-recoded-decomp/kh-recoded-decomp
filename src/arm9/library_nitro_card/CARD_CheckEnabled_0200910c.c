extern int func_02009100(void);
extern void OS_Terminate(void);

void CARD_CheckEnabled_0200910c(void) {
    if (func_02009100() == 0) {
        OS_Terminate();
    }
}
