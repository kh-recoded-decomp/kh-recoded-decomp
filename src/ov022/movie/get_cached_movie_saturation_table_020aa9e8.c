/* Returns a cached movie saturation table, copying its 0x300 bytes into a fast-memory arena when possible.
 * Evidence: Cache slot, byte count, copy, and fallback path in source.
 * Uncertainty: Table interpretation comes from read-only local reference analysis.
 * Source: src/overlays/ov024/calls/func_ov024_0208670c.c from khdays-decomp, CC0, commit ab832f38b943c15f461228968a89002e1a99c03e. */

extern void MIi_CpuCopyFast(const void *src, void *dest, unsigned int size);
extern int data_020b7df4[];
extern unsigned char data_020b7808[];

void *get_cached_movie_saturation_table_020aa9e8(void) {
    void *saturationTable;

    if (data_020b7df4[0] == 0) {
        if ((unsigned int)data_020b7df4[3] >= 0x300) {
            saturationTable = (void *)data_020b7df4[4];
            data_020b7df4[0] = (int)saturationTable;
            MIi_CpuCopyFast(data_020b7808, saturationTable, 0x300);
            data_020b7df4[4] += 0x300;
            data_020b7df4[3] -= 0x300;
        } else {
            return data_020b7808;
        }
    }
    return (void *)data_020b7df4[0];
}
