/* Allocates a command record, writes the command code and four arguments, then enqueues it.
 * Uncertainty: Command-code meanings are defined by callers. */
/* Recovered CC0 library C from Yokimitsuro/khdays-decomp, revision
 * ab832f38b943c15f461228968a89002e1a99c03e, libs/nitro/snd/calls/PushCommand_impl.c.
 * Original routine: PushCommand_impl. External references are
 * rebound to BK9E; subsystem identity is reviewed separately from matching. */
/* Fills one command slot and queues it; silently drops the command when the pool is dry. */
extern char *SND_AllocCommand(int wait);
extern void func_0200f048(char *cmd);

void func_0200ed4c(int cmd, int a, int b, int c, int d) {
    char *slot = SND_AllocCommand(1);
    if (slot == 0) {
        return;
    }
    *(int *)(slot + 4) = cmd;
    *(int *)(slot + 8) = a;
    *(int *)(slot + 0xc) = b;
    *(int *)(slot + 0x10) = c;
    *(int *)(slot + 0x14) = d;
    func_0200f048(slot);
}
