#include "nitro/types.h"

typedef struct {
    s16 frame;
    s16 width;
    s16 height;
    u16 flags;
    u8 mode;
    u8 pad_09[0x27];
    int elapsed;
} MovieState;

typedef struct {
    s8 mode;
    s8 frame;
    s16 width;
    s16 height;
} MovieParams;

extern struct { int reserved; MovieState *state; } contextData_020c0060;
extern u8 data_020608c8;
extern int func_ov001_020645c8(int flag);
extern void SetupFlaggedSelectionRecords_0204f778(void);
extern void FlushPendingFieldUpdate_020633d4(void);
extern BOOL QueueFieldUpdate_020633a0(int request);

void StartMoviePlayback_020bb4e0(MovieParams *params)
{
    u8 previous;

    contextData_020c0060.state->width = params->width;
    contextData_020c0060.state->height = params->height;
    contextData_020c0060.state->frame = params->frame;
    contextData_020c0060.state->flags = 3;
    contextData_020c0060.state->flags |= 0x20;
    contextData_020c0060.state->mode = params->mode;
    contextData_020c0060.state->elapsed = 0;
    if (func_ov001_020645c8(0x3609) || func_ov001_020645c8(0x360a)) {
        previous = data_020608c8;
        SetupFlaggedSelectionRecords_0204f778();
        if (previous != data_020608c8) {
            FlushPendingFieldUpdate_020633d4();
            QueueFieldUpdate_020633a0(0);
        }
    }
}
