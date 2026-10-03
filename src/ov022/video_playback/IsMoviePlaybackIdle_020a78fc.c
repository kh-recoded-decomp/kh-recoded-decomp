#include "nitro/types.h"

typedef struct {
    u8 pad_000[0x8b5];
    u8 playing;
} MoviePlayer;

extern MoviePlayer *data_ov022_020b7d80;

BOOL IsMoviePlaybackIdle_020a78fc(void) {
    return data_ov022_020b7d80->playing == 0;
}
