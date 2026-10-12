/* Both this entry and the decoder it dispatches to use ARM instructions. */
#pragma interworking off

typedef struct MovieChunkRecord MovieChunkRecord;

extern void DecodeMovieChunkType2Impl(MovieChunkRecord *chunk);

void DecodeMovieChunkType2(MovieChunkRecord *chunk)
{
    DecodeMovieChunkType2Impl(chunk);
}
