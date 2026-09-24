/* Resets the copied lookup-table allocation arena.
 * The cache slots are also used by the decode-table, saturation-table, and
 * pixel-clamp getters. Their accesses support the named fields below at BK9E
 * global 0x020b7df4; reserved words remain explicit and unnamed.
 * Adapted from khdays-decomp/src/overlays/ov024/calls/func_ov024_020865f8.c,
 * CC0-1.0, revision ab832f38b943c15f461228968a89002e1a99c03e.
 */
typedef struct MovieCacheArena {
    void *cachedSaturationTable;       /* +0x00 */
    void *cachedMovieDecodeTable;      /* +0x04 */
    void *cachedDecoderCode;           /* +0x08 */
    unsigned int tableBytesRemaining;  /* +0x0c */
    unsigned char *tableCopyCursor;    /* +0x10 */
    unsigned int codeBytesRemaining;   /* +0x14 */
    unsigned char *codeCopyCursor;     /* +0x18 */
    unsigned int reserved_1c;          /* +0x1c */
    void *cachedPixelClampTable;       /* +0x20 */
} MovieCacheArena;

extern MovieCacheArena movieCacheArena;

void ResetMovieLookupTableArena_020aa8d4(void *arenaBase, unsigned int arenaSize) {
    movieCacheArena.tableCopyCursor = (unsigned char *)arenaBase;
    movieCacheArena.tableBytesRemaining = arenaSize & ~3U;
    movieCacheArena.cachedMovieDecodeTable = 0;
    movieCacheArena.cachedSaturationTable = 0;
    movieCacheArena.cachedPixelClampTable = 0;
}
