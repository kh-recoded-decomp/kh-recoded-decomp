/* Invalidates the cache line covering the sound player status word and returns that word.
 * Uncertainty: Status bit meanings are not established. */
/* Recovered CC0 library C from Yokimitsuro/khdays-decomp, revision
 * ab832f38b943c15f461228968a89002e1a99c03e, libs/nitro/snd/calls/SND_GetPlayerStatus.c.
 * Original routine: SND_GetPlayerStatus. External references are
 * rebound to BK9E; subsystem identity is reviewed separately from matching. */
/* Reads the player status word the ARM7 writes into the shared work area. */
extern void DC_InvalidateRange(void *p, unsigned int len);
extern int *data_02059780;

int func_0200f59c(void) {
    DC_InvalidateRange(data_02059780 + 1, 4);
    return data_02059780[1];
}
