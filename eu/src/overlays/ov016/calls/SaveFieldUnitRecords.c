#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct Block16 {
    u32 words[4];
} Block16;

typedef struct Block32 {
    u32 words[8];
} Block32;

typedef struct UnitExtra {
    u32 words[25];
} UnitExtra;

typedef struct UnitRecord {
    VecFx32 position;
    u32 flags;
    u8 active : 1;
    u8 phase : 3;
    u8 kind : 4;
    s8 variant;
    s16 heading;
    u32 group : 4;
    u32 level : 8;
    u32 pad_14 : 20;
    u32 timer;
    Block16 motion;
    Block16 target;
    u32 state;
    Block32 params;
    union {
        VecFx32 vec;
        UnitExtra extra;
    } data;
} UnitRecord;

typedef struct UnitObject {
    u8 pad_00[0x38];
    VecFx32 position;
    u8 pad_44[0x3];
    s8 group;
    Block16 motion;
    Block16 target;
    u8 pad_68[0x8];
    u16 unk_70_lo : 6;
    u16 visible : 1;
    u16 unk_70_mid : 2;
    u16 phase : 3;
    u16 unk_70_hi : 4;
    s16 heading;
    u8 pad_74[0x2];
    s8 level;
    u8 pad_77[0xbd - 0x77];
    u8 unk_bd_lo : 4;
    u8 mode : 4;
    u8 unk_be_lo : 4;
    u8 kind : 4;
    s8 variant;
    u32 flags;
    u32 timer;
    u32 state;
    Block32 params;
    union {
        VecFx32 vec;
        UnitExtra *extra;
    } data;
} UnitObject;

typedef struct FieldUnit {
    u8 pad_00[0x3e];
    u16 count;
    u8 pad_40[0xc8 - 0x40];
    u16 slotCount : 5;
    u16 slotFlags : 11;
    u8 pad_ca[0x2];
    void *slotData;
} FieldUnit;

extern UnitRecord *AllocEffectBufferSlot(FieldUnit *unit, u32 size);
extern void *GetFieldUnitSlotRecord(FieldUnit *unit, UnitRecord *records);
extern UnitObject *func_ov001_02086384(FieldUnit *unit, int index);
extern void MIi_CpuCopyFast(const void *src, void *dst, u32 size);

void SaveFieldUnitRecords(FieldUnit *unit)
{
    UnitRecord *records = AllocEffectBufferSlot(unit, unit->count * sizeof(UnitRecord) + unit->slotCount * 0x1e0);
    void *slots = GetFieldUnitSlotRecord(unit, records);
    int i;

    for (i = 0; i < unit->count; i++) {
        UnitRecord *record = &records[i];
        UnitObject *object = func_ov001_02086384(unit, i);

        if ((object->flags & 0x2000000) || object->visible) {
            record->active = 1;
            record->position = object->position;
            record->group = object->group;
            record->phase = (u8)object->phase;
            record->kind = object->kind;
            record->variant = object->variant;
            record->level = object->level;
            record->flags = object->flags;
            record->state = object->state;
            record->params = object->params;
            record->heading = object->heading;
            if (object->mode >= 5) {
                record->data.extra = *object->data.extra;
            } else {
                record->data.vec = object->data.vec;
            }
            if (object->kind != 6) {
                if (object->flags & 0x20) {
                    record->timer = object->timer;
                }
                if (object->flags & 0x40) {
                    record->motion = object->motion;
                }
                if (object->flags & 0x8000) {
                    record->target = object->target;
                }
            }
        } else {
            record->active = 0;
        }
    }
    if (slots != NULL) {
        MIi_CpuCopyFast(unit->slotData, slots, unit->slotCount * 0x1e0);
    }
}
