#include "nitro/types.h"

typedef struct EventObject EventObject;

struct EventObject {
    u8 pad_000[0x1e8];
    void (*flaggedUpdate)(EventObject *object);
};

typedef struct EventEntry {
    u32 unk_00;
    EventObject *object;
    u8 pad_08[0x1c];
    u16 flags;
    u8 pad_26[0x2];
} EventEntry;

typedef struct EventContext {
    u32 unk_00;
    EventEntry entries[3];
    s32 entryCount;
    u8 pad_80[0xc];
    void *unk_8C;
} EventContext;

extern EventContext *g_eventContext_020a049c;

void RunFlaggedEventCallbacks_0206daa8(void)
{
    EventContext *context = g_eventContext_020a049c;
    EventEntry *entry;
    EventObject *object;
    int i;

    if (context == NULL || context->unk_8C == NULL) {
        return;
    }
    for (i = 0; i < context->entryCount; i++) {
        entry = &g_eventContext_020a049c->entries[i];
        if ((entry->flags & 2) > 0) {
            object = entry->object;
            if (object != NULL && object->flaggedUpdate != NULL) {
                object->flaggedUpdate(object);
            }
        }
    }
}
