#include "nitro/types.h"

typedef struct {
    void (*handler)(void);
    u8 pad_04[4];
    int param;
    u8 pad_0c[0x0c];
    u16 reserved0 : 2;
    u16 solid : 1;
    u16 reserved3 : 7;
    u16 typeFour : 1;
    u16 visible : 1;
    u16 active : 1;
    u16 reserved13 : 3;
    u8 pad_1a[2];
    u8 state;
    u8 id;
    u8 pad_1e[2];
} SlotEntry;

typedef struct {
    u8 pad_00[4];
    u8 state;
    u8 id;
    u8 pad_06[2];
    int param;
} SlotInfo;

typedef struct {
    int kind;
    int type;
    u8 pad_08[4];
    SlotInfo *info;
} SlotRecord;

extern void InitSlotEntry(SlotEntry *entry, void *source, int mirrored, int player);
extern void SpawnSourceMarker(void);

void InitSlotEntryFromRecord(SlotEntry *entry, void *source, int mirrored, SlotRecord *record, int player)
{
    InitSlotEntry(entry, source, mirrored, player);
    entry->state = record->info->state;
    entry->id = record->info->id;
    entry->param = record->info->param;
    entry->active = 1;
    if (record->type == 4) {
        entry->typeFour = 1;
    }
    switch (record->kind) {
    case 0x8c:
    case 0x8f:
        entry->visible = 1;
        break;
    case 0x5d:
    case 0x70:
    case 0x71:
    case 0x72:
    case 0x73:
        entry->active = 0;
        entry->visible = 1;
        break;
    case 0x8e:
        entry->solid = 1;
        entry->visible = 1;
        break;
    case 0x88:
    case 0x8d:
        entry->solid = 1;
        entry->visible = 1;
        entry->handler = SpawnSourceMarker;
        break;
    }
}
