#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x10];
    s16 counter;
} Ov045CounterState;

extern Ov045CounterState *g_ov045Context_020c0880;

/* Checks whether a counter field has gone negative. */
BOOL IsCounterNegative_020c0708(void)
{
    if (g_ov045Context_020c0880->counter < 0) {
        return TRUE;
    }
    return FALSE;
}
