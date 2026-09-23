/* Returns a pixel clamp table, caching a fast-memory copy when the arena has enough space. Evidence: Source implementation directly performs the described operations; see src/overlays/ov024/calls/func_ov024_0208677c.c. Uncertainty: No material uncertainty for the stated operation; game-specific use may depend on callers. Recovered from Days source src/overlays/ov024/calls/func_ov024_0208677c.c; CC0, commit ab832f38b943c15f461228968a89002e1a99c03e. */
extern void MIi_CpuCopyFast(const void *src, void *dest, unsigned int size);
extern int decoder_cache_arena[];
extern unsigned char pixel_clamp_table[];

void *GetCachedPixelClampTable_020aaa58(void) {
    void *table_pointer;

    if (decoder_cache_arena[8] == 0) {
        if ((unsigned int)decoder_cache_arena[3] >= 0x180) {
            table_pointer = (void *)decoder_cache_arena[4];
            decoder_cache_arena[8] = (int)table_pointer;
            MIi_CpuCopyFast(pixel_clamp_table, table_pointer, 0x180);
            decoder_cache_arena[4] += 0x180;
            decoder_cache_arena[3] -= 0x180;
        } else {
            return pixel_clamp_table;
        }
    }
    return (void *)decoder_cache_arena[8];
}
