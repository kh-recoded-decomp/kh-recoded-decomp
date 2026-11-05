/* Publishes one wave-data pointer to the ARM7 under the sound mutex. */
extern void LockSoundCommandMutex(void);
extern void SNDi_UnlockMutex(void);
extern void DC_StoreRange(void *p, unsigned int len);

void SND_SetWaveDataAddress(char *table, int slot, void *addr) {
    LockSoundCommandMutex();
    *(void **)(table + slot * 4 + 0x3c) = addr;
    DC_StoreRange(table + 0x3c + slot * 4, 4);
    SNDi_UnlockMutex();
}
