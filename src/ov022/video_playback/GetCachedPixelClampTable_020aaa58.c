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
