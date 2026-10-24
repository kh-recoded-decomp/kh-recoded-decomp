extern void OS_UnLockCartridge();
#ifndef NITRO_OS_INTERRUPT_STATE_H
extern void OS_RestoreInterrupts(int state);
#endif

void CTRDGi_UnlockByProcessor_020124a0(int id, int *ctx) {
    if (ctx[0] == 0) {
        OS_UnLockCartridge(id);
    }
    OS_RestoreInterrupts(ctx[1]);
}
