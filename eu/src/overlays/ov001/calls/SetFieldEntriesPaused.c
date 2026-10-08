#include "nitro/types.h"

typedef struct FieldActor {
    u8 pad_000[0x20c];
    void (*onPause)(struct FieldActor *actor, int unused, BOOL paused);
} FieldActor;

typedef struct {
    u32 unk0;
    FieldActor *actor;
    u8 pad_08[0x1c];
    u16 flags;
    u8 pad_26[2];
} FieldEntry;

typedef struct {
    u32 unk0;
    FieldEntry entries[3];
    int entryCount;
} FieldEntryManager;

extern FieldEntryManager *data_ov001_020a04bc;
extern void SetFieldSpritesFlag(BOOL paused);

void SetFieldEntriesPaused(BOOL paused)
{
    FieldEntryManager *manager = data_ov001_020a04bc;
    int i;

    if (manager == NULL) {
        return;
    }
    for (i = 0; i < manager->entryCount; i++) {
        FieldEntry *entry = &manager->entries[i];
        if (entry->actor != NULL) {
            if (paused) {
                entry->flags |= 0x10;
                if (entry->actor->onPause != NULL) {
                    entry->actor->onPause(entry->actor, 0, TRUE);
                }
            } else {
                entry->flags &= ~0x10;
                if (entry->actor->onPause != NULL) {
                    entry->actor->onPause(entry->actor, 0, FALSE);
                }
            }
        }
    }
    SetFieldSpritesFlag(paused);
}
