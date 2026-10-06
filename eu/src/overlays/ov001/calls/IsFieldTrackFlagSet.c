#include "nitro/types.h"

typedef struct TrackState {
    s16 defaultMain;
    s16 defaultSub;
    s16 main;
    s16 sub;
    u32 unk8;
    u32 mode : 2;
    u32 unk2 : 4;
    u32 subOverride : 1;
    u32 unk7 : 1;
    u32 flag : 1;
    u32 unk9 : 23;
} TrackState;

typedef struct FieldContext {
    u8 pad[0x208];
    TrackState track;
} FieldContext;

extern FieldContext *data_ov001_020a0480;

u32 IsFieldTrackFlagSet(void) {
    return data_ov001_020a0480->track.flag;
}
