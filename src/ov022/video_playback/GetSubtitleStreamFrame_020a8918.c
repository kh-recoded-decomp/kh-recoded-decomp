#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x48];
    int frame;
} SubtitleStream;

typedef struct {
    u32 unk_00;
    u32 unk_04;
    SubtitleStream *subtitles;
} MovieGlobals;

extern MovieGlobals data_ov022_020b7d88;

int GetSubtitleStreamFrame_020a8918(void) {
    return data_ov022_020b7d88.subtitles != NULL ? data_ov022_020b7d88.subtitles->frame : -1;
}
