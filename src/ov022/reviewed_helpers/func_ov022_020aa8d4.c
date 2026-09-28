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

void ResetMovieLookupTableArena_020aa8d4(void *arenaBase, unsigned int arenaSize) {
    movieCacheArena.tableCopyCursor = (unsigned char *)arenaBase;
    movieCacheArena.tableBytesRemaining = arenaSize & ~3U;
    movieCacheArena.cachedMovieDecodeTable = 0;
    movieCacheArena.cachedSaturationTable = 0;
    movieCacheArena.cachedPixelClampTable = 0;
}
