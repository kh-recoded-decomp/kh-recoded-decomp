#include "nitro/types.h"

typedef struct {
    u8 flag;
    u8 pad_01;
    s16 count;
} BusyCounterState;

extern BusyCounterState g_busyCounter_0205fde8;

void DecrementBusyCounterIfPositive_02025494(void)
{
    if (g_busyCounter_0205fde8.count > 0) {
        g_busyCounter_0205fde8.count--;
    }
}
