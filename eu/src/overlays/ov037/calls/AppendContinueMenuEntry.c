#include "nitro/types.h"

typedef struct ContinueMenuEntry {
    u32 value;
    u32 textId;
} ContinueMenuEntry;

typedef struct ContinueScreenContext {
    u8 pad_000[2];
    u16 entryCount;
} ContinueScreenContext;

extern ContinueScreenContext *gContinueScreenContext;

void AppendContinueMenuEntry(u32 value, u32 textId)
{
    u16 index = gContinueScreenContext->entryCount;
    ContinueMenuEntry *entries =
        (ContinueMenuEntry *)((u8 *)gContinueScreenContext + 0x1d4);

    entries[index].value = value;
    entries[index].textId = textId;
    gContinueScreenContext->entryCount++;
}
