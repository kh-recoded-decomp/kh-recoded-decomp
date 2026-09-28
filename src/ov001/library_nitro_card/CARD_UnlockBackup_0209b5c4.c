extern void *CARDi_LockResource();

void *CARD_UnlockBackup_0209b5c4(int id) {
    return CARDi_LockResource(id, 2);
}
