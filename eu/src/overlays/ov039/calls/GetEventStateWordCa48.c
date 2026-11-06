#include "nitro/types.h"

typedef struct EventState {
    u8 pad_0000[0xca48];
    u16 wordCa48;
} EventState;

extern EventState *gMenuOverlayWork;

u16 GetEventStateWordCa48(void)
{
    return gMenuOverlayWork->wordCa48;
}
