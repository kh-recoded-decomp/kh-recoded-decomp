#include "nitro/types.h"

typedef struct TrackState {
    u8 phase;
    u8 trackId;
    u16 timer;
} TrackState;

typedef struct Session {
    u8 pad_0000[0x27f8];
    TrackState track;
} Session;

extern Session *data_ov001_020a0460;
extern u32 func_02025948(u32 value);

void ResetTrackState_02062cf8(void) {
    Session *session = data_ov001_020a0460;
    TrackState *track = &session->track;
    func_02025948(-1);
    track->timer = 0;
    track->phase = 0;
}
