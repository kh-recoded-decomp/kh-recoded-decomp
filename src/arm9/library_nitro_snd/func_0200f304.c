/* Counts reserved sound commands in the global list with interrupts disabled.
 * Uncertainty: The distinction between reserved and pending commands is defined by surrounding queue logic. */
/* Recovered CC0 library C from Yokimitsuro/khdays-decomp, revision
 * ab832f38b943c15f461228968a89002e1a99c03e, libs/nitro/snd/calls/SND_CountReservedCommand.c.
 * Original routine: SND_CountReservedCommand. External references are
 * rebound to BK9E; subsystem identity is reviewed separately from matching. */
extern int OS_DisableInterrupts(void);
extern void OS_RestoreInterrupts(int state);
extern char *data_02057c50;

/* Length of the pending sound-command list. */
int func_0200f304(void) {
    int enabled = OS_DisableInterrupts();
    int count = 0;
    char *cmd = *(char **)&data_02057c50;
    while (cmd != 0) {
        cmd = *(char **)cmd;
        count++;
    }
    OS_RestoreInterrupts(enabled);
    return count;
}
