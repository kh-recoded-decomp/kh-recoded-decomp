#include "nitro/types.h"

typedef struct CueSource {
    u32 selection;
    void *unitResources;
    void *resourceData;
    void *modelObject;
} CueSource;

typedef struct EntryGroupDesc {
    char *name;
    u32 slotCount;
    u32 fixedSlots;
    u32 unk_0c;
    u32 unk_10;
} EntryGroupDesc;

typedef struct MotionRecord {
    u8 data[0x2c];
} MotionRecord;

typedef struct Entity {
    u8 pad_000[0x230];
    u8 *resourceHeader;
    u8 pad_234[0x76c - 0x234];
    MotionRecord motions[6];
    u8 pad_874[0x98c - 0x874];
    int (*mapKind)(int kind);
    u8 pad_990[0x9b4 - 0x990];
    u8 selection;
    u8 pad_9b5[3];
    int nameIndex;
    u8 pad_9bc[0xb68 - 0x9bc];
    u8 modelObject[0xfc8 - 0xb68];
    u8 unitResources[0x1070 - 0xfc8];
    u8 cues[0x1258 - 0x1070];
    u16 effectGroupId;
} Entity;

extern const char *data_0205615c[];
extern char data_ov053_020d2b60[];
extern char data_ov053_020d2b74[];
extern char data_ov053_020d2b84[];
extern char data_ov053_020d2b94[];
extern char data_ov053_020d2ba8[];
extern char data_ov053_020d2bbc[];
extern char data_ov053_020d2bcc[];
extern char data_ov053_020d2be0[];
extern char data_ov053_020d2bf4[];
extern char data_ov053_020d2c08[];
extern int OS_SPrintf_02002428(char *dst, const char *fmt, ...);
extern void AcquireSharedRecordState_020a9054(void *state, char *name, void *data, int context);
extern BOOL IsPlayerEntryFlagSet_02050014(u32 selection, int flag);
extern BOOL func_ov001_0206e2b0(void);
extern BOOL func_ov001_0206e31c(void);
extern BOOL func_ov001_020645c8(u32 value);
extern int func_ov001_02063a38(void);
extern void ZeroBytes0x14_020a8adc(EntryGroupDesc *desc);
extern u16 func_ov021_020a89a8(EntryGroupDesc *desc);
extern void func_ov053_020d23d8(Entity *entity);
extern void LoadOverlay053EntityModel_020d22dc(Entity *entity);
extern void LoadSelectionCues_020ad744(void *cues, CueSource *source);
extern void func_ov040_020bdf7c(Entity *entity, CueSource *source);
extern void func_ov010_020a17a0(Entity *entity);
extern int MapKindToSlotIndex_020d2a40(int kind);

void LoadOverlay053EntityResources_020d2414(Entity *entity)
{
    EntryGroupDesc group;
    CueSource source;
    char name[0x80];
    int context = entity->selection + 8;
    MotionRecord *record;

    OS_SPrintf_02002428(name, data_ov053_020d2b60, data_0205615c[entity->nameIndex]);
    AcquireSharedRecordState_020a9054(&entity->motions[0], name, entity->resourceHeader + 4, context);
    OS_SPrintf_02002428(name, data_ov053_020d2b74, data_0205615c[entity->nameIndex]);
    AcquireSharedRecordState_020a9054(&entity->motions[2], name, entity->resourceHeader + 4, context);
    record = &entity->motions[1];
    if (!IsPlayerEntryFlagSet_02050014(entity->selection, 0xc) || func_ov001_0206e2b0()) {
        OS_SPrintf_02002428(name, data_ov053_020d2b84, data_0205615c[entity->nameIndex]);
    } else {
        OS_SPrintf_02002428(name, data_ov053_020d2b94, data_0205615c[entity->nameIndex]);
    }
    AcquireSharedRecordState_020a9054(record, name, entity->resourceHeader + 4, context);
    OS_SPrintf_02002428(name, data_ov053_020d2ba8, data_0205615c[entity->nameIndex]);
    AcquireSharedRecordState_020a9054(&entity->motions[3], name, entity->resourceHeader + 4, context);
    record = &entity->motions[4];
    if (!func_ov001_0206e31c()) {
        OS_SPrintf_02002428(name, data_ov053_020d2bbc, data_0205615c[entity->nameIndex]);
    } else {
        OS_SPrintf_02002428(name, data_ov053_020d2bcc, data_0205615c[entity->nameIndex]);
    }
    AcquireSharedRecordState_020a9054(record, name, entity->resourceHeader + 4, context);
    if (!func_ov001_020645c8(0x3609) && !func_ov001_020645c8(0x360a) && !func_ov001_020645c8(0x360b)) {
        OS_SPrintf_02002428(name, data_ov053_020d2be0, data_0205615c[entity->nameIndex]);
    } else {
        OS_SPrintf_02002428(name, data_ov053_020d2bf4, data_0205615c[entity->nameIndex]);
    }
    AcquireSharedRecordState_020a9054(&entity->motions[5], name, entity->resourceHeader + 4, context);
    ZeroBytes0x14_020a8adc(&group);
    OS_SPrintf_02002428(name, data_ov053_020d2c08);
    group.name = name;
    group.slotCount = 1;
    group.fixedSlots = 1;
    group.unk_0c = 0;
    entity->effectGroupId = func_ov021_020a89a8(&group);
    func_ov053_020d23d8(entity);
    LoadOverlay053EntityModel_020d22dc(entity);
    source.selection = entity->selection;
    source.unitResources = entity->unitResources;
    source.resourceData = entity->resourceHeader + 4;
    source.modelObject = entity->modelObject;
    LoadSelectionCues_020ad744(entity->cues, &source);
    if (func_ov001_02063a38() == 6) {
        func_ov040_020bdf7c(entity, &source);
    }
    entity->mapKind = MapKindToSlotIndex_020d2a40;
    if (func_ov001_0206e31c()) {
        func_ov010_020a17a0(entity);
    }
}
