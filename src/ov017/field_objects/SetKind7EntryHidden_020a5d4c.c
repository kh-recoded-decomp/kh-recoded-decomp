#include "nitro/types.h"

typedef struct Kind7Entry {
    u8 pad_00[0x30];
    u16 statusFlags;
    u8 slot;
    u8 pad_33[0x1d];
    s8 state;
    u8 pad_51[3];
    u16 flags;
} Kind7Entry;

extern BOOL func_ov017_020a5dd0(Kind7Entry *entry);
extern void ActorSlot_SetFlag8ByIndex_02036120(int index, BOOL enable);

void SetKind7EntryHidden_020a5d4c(Kind7Entry *entry, BOOL hidden)
{
    BOOL visible;
    BOOL busy;

    if (hidden) {
        entry->flags |= 8;
        entry->statusFlags &= ~0x10;
        entry->statusFlags &= ~8;
    } else {
        entry->flags &= ~8;
        entry->statusFlags |= 0x10;
        entry->statusFlags |= 8;
    }
    if (entry->statusFlags & 4) {
        visible = FALSE;
        if (!func_ov017_020a5dd0(entry)) {
            busy = TRUE;
            if (entry->state != 2 && entry->state != 1) {
                busy = FALSE;
            }
            if (!busy) {
                visible = TRUE;
            }
        }
        ActorSlot_SetFlag8ByIndex_02036120(entry->slot, visible);
    }
}
