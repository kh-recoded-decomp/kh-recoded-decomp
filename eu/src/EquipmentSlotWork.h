#ifndef EQUIPMENT_SLOT_WORK_H
#define EQUIPMENT_SLOT_WORK_H

#include "nitro/types.h"

typedef struct EquipmentRecordEntry {
    u16 kind : 2;
    u16 flags : 3;
    u16 levelProgress : 11;
    u16 active : 1;
    u16 level : 7;
    u16 category : 8;
} EquipmentRecordEntry;

/* Two cached records move with each equipped pair of command IDs. */
typedef struct EquipmentSlotWork {
    s32 state;
    /* Level-progress limit for records, maximum uses for items (state 3). */
    u32 limit;
    EquipmentRecordEntry entry;
} EquipmentSlotWork;

typedef char EquipmentSlotWorkSizeCheck[sizeof(EquipmentSlotWork) == 12 ? 1 : -1];
typedef char EquipmentRecordEntrySizeCheck[sizeof(EquipmentRecordEntry) == 4 ? 1 : -1];

/* Complete records in this recovered BSS range; later storage is separate. */
extern EquipmentSlotWork gEquipmentSlotWork[12];

#endif
