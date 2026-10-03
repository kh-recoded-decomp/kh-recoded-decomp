#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef void (*UnitCallback)(void);

typedef struct UnitDesc {
    u8 slotCount;
    s8 cellCount;
    u8 pad_02[0x2];
    int linkCount;
} UnitDesc;

typedef struct UnitRecord {
    u8 pad_00[0x10];
    u8 active : 1;
    u8 rest : 7;
    u8 pad_11[0xc4 - 0x11];
} UnitRecord;

typedef struct UnitObject {
    u8 pad_00[0x4];
    struct FieldUnit *owner;
    u8 pad_08[0x33 - 0x8];
    u8 index;
    u8 pad_34[0x70 - 0x34];
    u16 drawFlags;
} UnitObject;

typedef struct FieldUnit {
    UnitCallback callbacks[15];
    u16 stride;
    u16 count;
    u8 *entries;
    fx32 radius;
    fx32 height;
    fx32 scale[3];
    u8 layer;
    u8 pad_59;
    u8 category;
    u8 pad_5b[0x5];
    void *slots[21];
    s16 activeIndex;
    u8 pad_b6[0x2];
    void *cells;
    void *links;
    u16 cellCount;
    u16 linkCount;
    UnitRecord *records;
    u16 slotCount : 5;
    u16 slotFlags : 11;
    u16 slotCursor;
    void *slotData;
    void *workBuffer;
} FieldUnit;

extern FieldUnit *CreateEntryPool_02086258(int headerSize, int entrySize, int count);
extern UnitObject *func_ov001_0208635c(FieldUnit *unit, int index);
extern void *NNSi_FndAllocFromDefaultHeapEx_0202a19c(u32 size, int alignment);
extern void func_01ff88c4(void *dst, u32 value, u32 size);
extern void MIi_CpuCopyFast_01ff878c(const void *src, void *dst, u32 size);
extern void func_ov016_020a5f18(UnitObject *object);
extern void LoadFieldUnitModel_020a4dd8(void);
extern void RefreshFieldObjectPhase_020a5b24(void);
extern void FreeHeapRecord_020a5064(void);
extern void func_ov016_020a5c3c(void);
extern void SaveFieldUnitRecords_020a5d18(void);
extern void func_ov016_020a5b94(void);
extern void func_ov016_020a5084(void);
extern void func_ov016_020a5340(void);
extern void DispatchCollisionUnlessSameSlot_020a52b8(void);
extern void func_ov016_020a52f4(void);
extern void func_ov016_020a5b20(void);
extern void GetFieldUnitPosition_020a5c14(void);
extern void HasFieldUnitPhase_020a5c28(void);
extern void DrawFieldUnitObject_020a537c(void);

FieldUnit *CreateFieldUnit_020a60dc(int count, UnitDesc *desc, UnitRecord *records)
{
    FieldUnit *unit = CreateEntryPool_02086258(sizeof(FieldUnit), 0xf8, count);
    int i;
    int index;
    u32 size;
    u8 slotCount;

    unit->height = 0;
    unit->layer = 3;
    unit->scale[0] = 0x1800;
    unit->scale[1] = 0x1800;
    unit->scale[2] = 0x1800;
    unit->radius = 0x3000;
    unit->callbacks[0] = LoadFieldUnitModel_020a4dd8;
    unit->callbacks[1] = RefreshFieldObjectPhase_020a5b24;
    unit->callbacks[2] = NULL;
    unit->callbacks[4] = FreeHeapRecord_020a5064;
    unit->callbacks[5] = func_ov016_020a5c3c;
    unit->callbacks[13] = SaveFieldUnitRecords_020a5d18;
    unit->callbacks[6] = func_ov016_020a5b94;
    unit->callbacks[7] = func_ov016_020a5084;
    unit->callbacks[8] = func_ov016_020a5340;
    unit->callbacks[9] = DispatchCollisionUnlessSameSlot_020a52b8;
    unit->callbacks[10] = func_ov016_020a52f4;
    unit->callbacks[3] = func_ov016_020a5b20;
    unit->callbacks[11] = GetFieldUnitPosition_020a5c14;
    unit->callbacks[12] = HasFieldUnitPhase_020a5c28;
    unit->callbacks[14] = DrawFieldUnitObject_020a537c;
    unit->category = 9;
    unit->records = records;
    for (i = 0; i < 21; i++) {
        unit->slots[i] = NULL;
    }
    unit->activeIndex = -1;
    if (records != NULL) {
        for (index = 0; index < count; index++) {
            UnitObject *object = func_ov001_0208635c(unit, index);

            object->owner = unit;
            object->index = index;
            if (records[index].active) {
                object->drawFlags |= 0x40;
                func_ov016_020a5f18(object);
            }
        }
    }
    if (desc != NULL) {
        u32 cellSize = desc->cellCount;

        size = desc->linkCount * 0x14;
        unit->cellCount = cellSize;
        cellSize *= 4;
        unit->cells = NNSi_FndAllocFromDefaultHeapEx_0202a19c(cellSize, 4);
        func_01ff88c4(unit->cells, 0, cellSize);
        if (size != 0) {
            unit->linkCount = desc->linkCount;
            unit->links = NNSi_FndAllocFromDefaultHeapEx_0202a19c(size, 4);
            func_01ff88c4(unit->links, 0, size);
        }
        slotCount = desc->slotCount;
        if (slotCount != 0) {
            unit->slotCount = slotCount;
            size = slotCount * 0x1e0;
            unit->slotData = NNSi_FndAllocFromDefaultHeapEx_0202a19c(size, 4);
            func_01ff88c4(unit->slotData, 0, size);
            unit->slotCursor = 0;
            if (unit->records != NULL) {
                MIi_CpuCopyFast_01ff878c(&unit->records[unit->count], unit->slotData, unit->slotCount * 0x1e0);
            }
            unit->workBuffer = NNSi_FndAllocFromDefaultHeapEx_0202a19c(0x168, 4);
        } else {
            unit->slotData = NULL;
            unit->workBuffer = NULL;
        }
    }
    return unit;
}
