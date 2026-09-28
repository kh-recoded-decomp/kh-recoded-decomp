typedef struct MovieCacheArena {
    void *cachedSaturationTable;
    void *cachedMovieDecodeTable;
    void *cachedDecoderCode;
    unsigned int tableBytesRemaining;
    unsigned char *tableCopyCursor;
    unsigned int codeBytesRemaining;
    unsigned char *codeCopyCursor;
    unsigned int reserved_1c;
    void *cachedPixelClampTable;
} MovieCacheArena;

extern MovieCacheArena movieCacheArena;

void ResetMovieDecoderCodeArena_020aa8b4(void *arenaBase, unsigned int arenaSize) {
    movieCacheArena.codeCopyCursor = (unsigned char *)arenaBase;
    movieCacheArena.codeBytesRemaining = arenaSize & ~3U;
    movieCacheArena.cachedDecoderCode = 0;
}
