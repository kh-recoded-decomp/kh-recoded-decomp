#include "nitro/types.h"

typedef struct EntryGroupDesc {
    u32 unk_00;
    u32 paletteParams;
    u32 mode;
    u32 vramParams;
    u32 fixedSlots;
} EntryGroupDesc;

typedef struct PaletteIdTable {
    u32 ids[7];
} PaletteIdTable;

typedef struct CueEntry {
    s16 id;
    u8 pad_02[10];
} CueEntry;

typedef struct CueList {
    CueEntry entries[21];
    u8 pad_fc[4];
    int count;
} CueList;

typedef struct SelectionRecord {
    u8 kind;
    u8 pad_01[0x2b];
    CueList cues;
} SelectionRecord;

typedef struct MotionRecord {
    u8 data[0x2c];
} MotionRecord;

typedef struct Entity {
    u8 pad_000[0x230];
    u8 *resourceHeader;
    u8 pad_234[0x76c - 0x234];
    MotionRecord motions[3];
    u8 pad_7f0[0x98c - 0x7f0];
    int (*mapCode)(int code);
    u8 pad_990[0x9b4 - 0x990];
    u8 selection;
    u8 pad_9b5[3];
    int nameIndex;
    u8 pad_9bc[0x1278 - 0x9bc];
    s16 rewardGroupIds[7];
} Entity;

extern const char *data_0205615c[];
extern char data_ov054_020d36a0[];
extern char data_ov054_020d36b4[];
extern char data_ov054_020d36c8[];
extern char data_ov054_020d36d8[];
extern PaletteIdTable data_ov054_020d3654;
extern int OS_SPrintf_02002428(char *dst, const char *fmt, ...);
extern void AcquireSharedRecordState_020a9054(void *state, char *name, void *data, int context);
extern BOOL IsPlayerEntryFlagSet_02050014(u32 selection, int flag);
extern u32 func_ov001_0206dba0(int index);
extern SelectionRecord *func_0204f768(u32 index);
extern void ZeroBytes0x14_020a8adc(EntryGroupDesc *desc);
extern s16 func_ov021_020a89a8(EntryGroupDesc *desc);
extern int MapCodeToSlotIndex_020d271c(int code);

void LoadOverlay054EntityResources_020d2320(Entity *entity)
{
    char name[0x80];
    PaletteIdTable table;
    EntryGroupDesc group;
    int context = entity->selection + 8;
    MotionRecord *record;
    u32 vramBase;
    u32 mask;
    int i;
    SelectionRecord *selection;
    CueList *cues;
    u32 params;

    OS_SPrintf_02002428(name, data_ov054_020d36a0, data_0205615c[entity->nameIndex]);
    AcquireSharedRecordState_020a9054(&entity->motions[0], name, entity->resourceHeader + 4, context);
    OS_SPrintf_02002428(name, data_ov054_020d36b4, data_0205615c[entity->nameIndex]);
    AcquireSharedRecordState_020a9054(&entity->motions[2], name, entity->resourceHeader + 4, context);
    record = &entity->motions[1];
    if (!IsPlayerEntryFlagSet_02050014(entity->selection, 0xc)) {
        OS_SPrintf_02002428(name, data_ov054_020d36c8, data_0205615c[entity->nameIndex]);
    } else {
        OS_SPrintf_02002428(name, data_ov054_020d36d8, data_0205615c[entity->nameIndex]);
    }
    AcquireSharedRecordState_020a9054(record, name, entity->resourceHeader + 4, context);
    vramBase = func_ov001_0206dba0(3);
    table = data_ov054_020d3654;
    mask = 0;
    selection = func_0204f768(entity->selection);
    cues = &selection->cues;
    for (i = 0; i < cues->count; i++) {
        switch (cues->entries[i].id) {
        case 0xb7:
            mask |= 1;
            break;
        case 0xb8:
            mask |= 2;
            break;
        case 0xb9:
            mask |= 4;
            break;
        case 0xba:
            mask |= 8;
            break;
        case 0xbb:
            mask |= 0x10;
            break;
        case 0xbc:
            mask |= 0x20;
            break;
        case 0xbd:
            mask |= 0x40;
            break;
        }
    }
    params = 0x80000000 | (((vramBase + 0x8000) & 0xfffffc) << 7);
    for (i = 0; i < 7; i++) {
        entity->rewardGroupIds[i] = -1;
        if (mask & (1 << i)) {
            ZeroBytes0x14_020a8adc(&group);
            group.vramParams = (table.ids[i] & 0x1ff) | params;
            group.paletteParams = ((table.ids[i] + 1) & 0x1ff) | params;
            group.mode = 3;
            group.fixedSlots = 1;
            entity->rewardGroupIds[i] = func_ov021_020a89a8(&group);
        }
    }
    entity->mapCode = MapCodeToSlotIndex_020d271c;
}
