extern void func_020b81e8(int owner, int entry, unsigned short editValueA, unsigned short editValueB);
extern void func_020b8210(int owner, int entry);

void apply_all_pending_entry_edits_020b84f4(int owner, int editList, unsigned short editValueA, unsigned short editValueB) {
    int entryIndex = 0;
    int entryCount = *(unsigned short *)(editList + 2);
    if (entryCount > 0) {
        do {
            func_020b81e8(owner, (*(int **)(editList + 0x2c))[entryIndex], editValueA, editValueB);
            entryIndex = entryIndex + 1;
        } while (entryIndex < (int)*(unsigned short *)(editList + 2));
    }
    func_020b8210(owner,
        *(int *)(*(int *)(editList + 0x2c) + *(unsigned short *)(editList + 4) * 4));
}
