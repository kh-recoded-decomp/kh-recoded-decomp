#include "nitro/types.h"

typedef struct {
    u8 flag;
    u8 pad_01;
    s16 count;
} BusyCounterState;

extern BusyCounterState g_busyCounter_0205fde8;

void IncrementBusyCounter_020254a8(void)
{
    g_busyCounter_0205fde8.count++;
}
