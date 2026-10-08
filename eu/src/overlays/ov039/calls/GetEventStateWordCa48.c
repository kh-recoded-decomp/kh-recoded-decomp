#include "nitro/types.h"

typedef struct EventState {
    u8 pad_0000[0xca48];
    u16 wordCa48;
} EventState;

extern EventState *data_ov039_020bea20;

u16 GetEventStateWordCa48(void)
{
    return data_ov039_020bea20->wordCa48;
}
