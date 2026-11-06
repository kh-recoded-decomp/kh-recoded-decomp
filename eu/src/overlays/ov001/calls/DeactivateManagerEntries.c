#include "nitro/types.h"

typedef struct ManagedObject ManagedObject;

struct ManagedObject {
    u8 pad_000[0x20c];
    void (*notify)(ManagedObject *object, int kind, int arg);
};

typedef struct ManagerEntry {
    u32 unk_00;
    ManagedObject *object;
    u8 pad_08[0x1c];
    u16 flags;
    u16 unk_26;
} ManagerEntry;

typedef struct FieldManager {
    u32 unk_00;
    ManagerEntry entries[3];
    int entryCount;
} FieldManager;

extern FieldManager *gManagedActorGlobals;
extern s32 GetFieldSessionState(void);
extern void SetMenuHighlight(int value);
extern void ConfigureChannelSlot(int kind, int value, int index);
extern void SetFieldMessageLoaderUpdatesPaused(u32 enabled);

void DeactivateManagerEntries(void)
{
    FieldManager *manager = gManagedActorGlobals;
    int entryIndex;

    if (manager == NULL) {
        return;
    }
    if (GetFieldSessionState() != 7) {
        SetMenuHighlight(0);
    }
    entryIndex = 0;
    ConfigureChannelSlot(0, 0, 0);
    SetFieldMessageLoaderUpdatesPaused(0);
    for (; entryIndex < manager->entryCount; entryIndex++) {
        ManagerEntry *entry = &manager->entries[entryIndex];
        if (entry->object != NULL) {
            entry->flags &= ~4;
            if (entry->object->notify != NULL) {
                entry->object->notify(entry->object, 1, 0);
            }
        }
    }
}
