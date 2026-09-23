/* Returns a decoder table, caching a fast-memory copy when the arena has enough space. Evidence: Source implementation directly performs the described operations; see src/overlays/ov024/calls/func_ov024_0208669c.c. Uncertainty: No material uncertainty for the stated operation; game-specific use may depend on callers. Recovered from Days source src/overlays/ov024/calls/func_ov024_0208669c.c; CC0, commit ab832f38b943c15f461228968a89002e1a99c03e. */
extern void MIi_CpuCopyFast(const void *src, void *dest, unsigned int size);
extern int decoder_cache_arena[];
extern unsigned char movie_decode_table[];

void *GetCachedMovieDecodeTable_020aa978(void) {
    void *table_pointer;

    if (decoder_cache_arena[1] == 0) {
        if ((unsigned int)decoder_cache_arena[3] >= 0x2100) {
            table_pointer = (void *)decoder_cache_arena[4];
            decoder_cache_arena[1] = (int)table_pointer;
            MIi_CpuCopyFast(movie_decode_table, table_pointer, 0x2100);
            decoder_cache_arena[4] += 0x2100;
            decoder_cache_arena[3] -= 0x2100;
        } else {
            return movie_decode_table;
        }
    }
    return (void *)decoder_cache_arena[1];
}
