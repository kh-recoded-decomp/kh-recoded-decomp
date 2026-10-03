#include "nitro/types.h"

typedef struct {
    u32 unk_00;
    u32 unk_04;
    void *subtitles;
} MovieGlobals;

typedef struct {
    u8 pad_00[0x58];
    int subtitlesDone;
} MovieFileBank;

extern MovieGlobals data_ov022_020b7d88;
extern MovieFileBank data_ov022_020b7d94;

extern int runMovieSlotState_020a8730(void *timer);

int TickSubtitleTimer_020a88c4(void) {
    int done = runMovieSlotState_020a8730(data_ov022_020b7d88.subtitles);

    if (done) {
        data_ov022_020b7d94.subtitlesDone = 1;
    }
    return done;
}
