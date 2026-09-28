/* Disables interrupts around sound-alarm dispatch and restores the previous interrupt state afterward.
 * Uncertainty: This identifies a shared library operation; the particular scene, asset or gameplay caller using it is not established. */
/* Recovered CC0 library C from Yokimitsuro/khdays-decomp, revision
 * ab832f38b943c15f461228968a89002e1a99c03e, libs/nitro/pxi/calls/PxiFifoCallback.c.
 * Original routine: PxiFifoCallback. External references are
 * rebound to BK9E; subsystem identity is reviewed separately from matching. */
/* Runs the sound alarm handler with interrupts disabled. */
extern int OS_DisableInterrupts(void);
extern void SNDi_CallAlarmHandler(int data);
extern void OS_RestoreInterrupts(int state);

void Sound_DispatchAlarmWithInterruptsDisabled_0200f398(int unused, int data) {
    int state = OS_DisableInterrupts();
    SNDi_CallAlarmHandler(data);
    OS_RestoreInterrupts(state);
}
