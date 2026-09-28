extern int OS_DisableInterrupts(void);
extern void OS_RestoreInterrupts(int state);
extern int func_02002f24(void);

int CheckCommandProcessorReady_0200f490(void) {
    volatile unsigned int *mailbox_status_register = (volatile unsigned int *)0x04fff200;
    int interrupt_state;
    unsigned int mailbox_status;
    if (func_02002f24() == 0) {
        return 1;
    }
    interrupt_state = OS_DisableInterrupts();
    *mailbox_status_register = 0x10;
    mailbox_status = *mailbox_status_register;
    OS_RestoreInterrupts(interrupt_state);
    return mailbox_status != 0;
}
