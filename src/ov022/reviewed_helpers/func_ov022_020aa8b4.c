/* Resets the copied decoder-code allocation arena.
 * The cached code pointer, remaining-byte count, and next-copy pointer are
 * shared with GetCachedMovieDecoderCode_020aa8fc. The type follows those
 * observed accesses at BK9E global 0x020b7df4; reserved words stay unnamed.
 * Adapted from khdays-decomp/src/overlays/ov024/calls/func_ov024_020865d8.c,
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

void ResetMovieDecoderCodeArena_020aa8b4(void *arenaBase, unsigned int arenaSize) {
    movieCacheArena.codeCopyCursor = (unsigned char *)arenaBase;
    movieCacheArena.codeBytesRemaining = arenaSize & ~3U;
    movieCacheArena.cachedDecoderCode = 0;
}
