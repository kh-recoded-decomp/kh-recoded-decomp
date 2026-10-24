extern int OS_DisableInterrupts(void);
extern void SNDi_CallAlarmHandler(int data);
#ifndef NITRO_OS_INTERRUPT_STATE_H
extern void OS_RestoreInterrupts(int state);
#endif

void Sound_DispatchAlarmWithInterruptsDisabled_0200f398(int unused, int data) {
    int state = OS_DisableInterrupts();
    SNDi_CallAlarmHandler(data);
    OS_RestoreInterrupts(state);
}
