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

extern FieldManager *g_manager_020a049c;
extern s32 func_ov001_02063a38(void);
extern void func_ov001_0206c2f8(int value);
extern void func_ov001_0206ca68(int kind, int value, int index);
extern void func_ov001_0206cab4(u32 enabled);

void DeactivateManagerEntries_0206e3d8(void)
{
    FieldManager *manager = g_manager_020a049c;
    int entryIndex;

    if (manager == NULL) {
        return;
    }
    if (func_ov001_02063a38() != 7) {
        func_ov001_0206c2f8(0);
    }
    entryIndex = 0;
    func_ov001_0206ca68(0, 0, 0);
    func_ov001_0206cab4(0);
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
