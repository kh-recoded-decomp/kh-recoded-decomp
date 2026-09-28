typedef unsigned char MovieU8;
typedef struct MovieStreamResourceHeads {
    void *reader_000;
    MovieU8 reserved_004[0x54];
    void *audioTracks_058;
    void **lumaSlots_05c;
    void **chromaSlots_060;
    void **planeSlots_064;
    void *scaleLuma_068;
    void *scaleChroma_06c;
    void *scratchA_070;
    void *scratchB_074;
    MovieU8 reserved_078[0x1c];
    void *frameIndex_094;
} MovieStreamResourceHeads;

MovieStreamResourceHeads *initializeMovieStreamResources_020a93ec(MovieStreamResourceHeads *stream)
{
    stream->reader_000 = 0;
    stream->lumaSlots_05c = 0;
    stream->chromaSlots_060 = 0;
    stream->scaleLuma_068 = 0;
    stream->scaleChroma_06c = 0;
    stream->scratchA_070 = 0;
    stream->scratchB_074 = 0;
    stream->planeSlots_064 = 0;
    stream->audioTracks_058 = 0;
    stream->frameIndex_094 = 0;
    return stream;
}
