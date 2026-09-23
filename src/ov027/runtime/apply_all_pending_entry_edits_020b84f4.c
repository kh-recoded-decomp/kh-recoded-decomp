/* Applies the supplied edits to each listed entry and then commits the currently selected entry.
 * Evidence: Count, entry pointer array, selected index, and two helper calls in source.
 * Uncertainty: Exact edited property is opaque to this function.
 * Source: src/overlays/ov002/calls/func_ov002_02054bcc.c from khdays-decomp, CC0, commit ab832f38b943c15f461228968a89002e1a99c03e. */

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
