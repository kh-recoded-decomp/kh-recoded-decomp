extern void *CARDi_LockResource();

void *CARD_UnlockBackup_020091ac(int id) {
    return CARDi_LockResource(id, 2);
}
