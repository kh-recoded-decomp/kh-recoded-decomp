/* Stores a wave-data pointer in an archive table slot under the sound mutex and flushes the updated pointer.
 * Uncertainty: Caller supplies the table and slot. */
/* Recovered CC0 library C from Yokimitsuro/khdays-decomp, revision
 * ab832f38b943c15f461228968a89002e1a99c03e, libs/nitro/snd/calls/SND_SetWaveDataAddress.c.
 * Original routine: SND_SetWaveDataAddress. External references are
 * rebound to BK9E; subsystem identity is reviewed separately from matching. */
/* Publishes one wave-data pointer to the ARM7 under the sound mutex. */
extern void func_0200edc8(void);
extern void func_0200eddc(void);
extern void DC_StoreRange(void *p, unsigned int len);

void func_0200fa9c(char *table, int slot, void *addr) {
    func_0200edc8();
    *(void **)(table + slot * 4 + 0x3c) = addr;
    DC_StoreRange(table + 0x3c + slot * 4, 4);
    func_0200eddc();
}
