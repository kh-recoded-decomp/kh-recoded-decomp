#include "nitro/types.h"

typedef struct MovieStream {
    u8 pad_00[0x58];
    s32 entryIndex;
    s32 stateCounter;
    s32 mode;
} MovieStream;

extern void SubtitleText_BeginDraw(MovieStream *stream);
extern int advanceMovieStreamWindow(MovieStream *stream);

BOOL func_ov003_020649fc(MovieStream *stream, int event)
{
    s32 *counter;

    switch (stream->mode) {
    case 0:
        counter = &stream->entryIndex;
        break;
    case 1:
    case 2:
    case 3:
    case 4:
        counter = &stream->stateCounter;
        break;
    }

    switch (event) {
    case 1:
        SubtitleText_BeginDraw(stream);
        break;
    case 3:
        (*counter)++;
        break;
    case 8:
        stream->mode = 1;
        stream->stateCounter = 0;
        break;
    case 9:
        stream->mode = 2;
        stream->stateCounter = 0;
        break;
    case 11:
        stream->mode = 3;
        stream->stateCounter = 0;
        break;
    case 12:
        stream->mode = 4;
        stream->stateCounter = 0;
        break;
    case 10:
        advanceMovieStreamWindow(stream);
        break;
    }
    return TRUE;
}
