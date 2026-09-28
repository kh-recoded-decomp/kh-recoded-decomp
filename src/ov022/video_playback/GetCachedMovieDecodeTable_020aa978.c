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
