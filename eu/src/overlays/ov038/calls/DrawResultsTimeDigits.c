#include "nitro/types.h"

#define SetSpriteFrame func_0204f218

typedef struct ResultsSpritePool { u8 data[0x6434]; } ResultsSpritePool;
typedef struct ResultsContext {
    u8 reserved00[0x40];
    ResultsSpritePool pools[2];
} ResultsContext;

extern ResultsContext *data_ov038_020bd164;
extern void SetSpriteFrame(ResultsSpritePool *pool, int index, u16 frame);
extern void IndexedRecords_SetFlag2(ResultsSpritePool *pool, int index, BOOL enabled);

#pragma push
#pragma opt_loop_invariants off
void DrawResultsTimeDigits(int poolIndex, int firstRecord, u32 totalSeconds)
{
    struct { u32 seconds, minutes, hours; } time;
    ResultsContext *context = data_ov038_020bd164;
    int remaining;
    int divisor;
    BOOL showDigits = FALSE;
    int position;
    u16 glyph;

    ResultsSpritePool *pool = &context->pools[poolIndex];
    time.hours = totalSeconds / 3600;
    time.minutes = (totalSeconds / 60) % 60;
    time.seconds = totalSeconds % 60;
    /* Display HHH:MM:SS, hiding only the optional hundreds-of-hours zero. */
    for (position = 0; position < 9; position++) {
        if (position == 0) {
            remaining = time.hours;
            divisor = 100;
        }
        if (position == 4) {
            remaining = time.minutes;
            divisor = 10;
        }
        if (position == 7) {
            remaining = time.seconds;
            divisor = 10;
        }
        if (position == 3 || position == 6) {
            glyph = 11;
        } else {
            glyph = remaining / divisor;
        }
        if (glyph != 0 || position == 1) {
            showDigits = TRUE;
        }
        remaining %= divisor;
        divisor /= 10;
        SetSpriteFrame(pool, firstRecord + position, glyph);
        IndexedRecords_SetFlag2(pool, firstRecord + position, showDigits);
    }
}
#pragma pop
