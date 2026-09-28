extern void *CARDi_LockResource();

void *CARD_UnlockBackup_0209b644(int id) {
    return CARDi_LockResource(id, 2);
}
