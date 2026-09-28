#include "nitro/types.h"

typedef struct {
    u8 data[0xc];
} HudEntry;

typedef struct {
    u8 pad_000[0x6e4];
    HudEntry *entries;
} HudContext;

typedef struct {
    u32 unk_00;
    HudContext *context;
} HudGlobals;

extern HudGlobals data_020a04a4;

HudEntry *GetHudEntry_02072eb0(int entryIndex) {
    return &data_020a04a4.context->entries[entryIndex];
}
