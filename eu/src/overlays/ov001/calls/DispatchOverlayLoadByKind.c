#include "nitro/types.h"

typedef struct {
    u16 id : 10;
    u16 kind : 6;
    u16 pad;
    void *handle;
} SlotEntry;

typedef struct {
    u8 pad[0x138];
    SlotEntry slots[1];
} SlotTable;

typedef struct {
    u8 pad[0x214];
    u32 unk0 : 4;
    u32 busy : 1;
} FlagBlock;

extern SlotTable *data_ov001_020a04fc;
extern FlagBlock *data_ov001_020a0480;
extern BOOL IsSessionFlagSet(u32 value);
extern int CreatePanelEntryPool(u16 id, int arg);
extern int CreateKind2EntryPool(u16 id, int arg);
extern int CreateKind3EntryPool(u16 id, int arg);
extern int CreateKind4EntryPool(u16 id, int arg);
extern int GetActorVelocity(u16 id, int arg, void *handle);
extern int CreateKind6EntryPool(u16 id, int arg);
extern int CreateKind7EntryPool(u16 id, int arg);
extern int CreateGridEntryPool(u16 id, int arg);
extern int CreateFieldUnit(u16 id, int arg, void *handle);

int DispatchOverlayLoadByKind(u32 kind, int slot, u32 id, int arg) {
    SlotTable *table = data_ov001_020a04fc;
    int result = 0;
    void *handle = NULL;

    if (!IsSessionFlagSet(0x3614) && !data_ov001_020a0480->busy) {
        void *found = table->slots[slot].handle;
        if (found != NULL && id == table->slots[slot].id && kind == table->slots[slot].kind) {
            handle = found;
        }
    }

    switch (kind) {
    case 1: result = CreatePanelEntryPool(id, arg); break;
    case 2: result = CreateKind2EntryPool(id, arg); break;
    case 3: result = CreateKind3EntryPool(id, arg); break;
    case 4: result = CreateKind4EntryPool(id, arg); break;
    case 5: result = GetActorVelocity(id, arg, handle); break;
    case 6: result = CreateKind6EntryPool(id, arg); break;
    case 7: result = CreateKind7EntryPool(id, arg); break;
    case 8: result = CreateGridEntryPool(id, arg); break;
    case 9: result = CreateFieldUnit(id, arg, handle); break;
    }

    return result;
}
