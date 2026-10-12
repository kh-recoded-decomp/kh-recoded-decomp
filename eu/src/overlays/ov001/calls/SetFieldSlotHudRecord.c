#include "src/overlays/ov001/FieldUiPatterns.h"

typedef struct FieldSlotHud {
    u8 reserved000[0x480];
    u32 reservedFlags : 20;
    u32 slotLabelsDirty : 1;
    u32 remainingFlags : 11;
    u8 reserved484[0x174];
    void *slotRecords[3];
} FieldSlotHud;

typedef struct FieldHudHandle {
    u32 reserved00;
    FieldSlotHud *manager;
} FieldHudHandle;

extern FieldHudHandle data_ov001_020a04c4;
extern BOOL data_0205fde4;
extern BOOL IsHudFlag9Set(void);
extern void *GetSceneTagTracker(void);
extern void *FindActiveRecordById(void *pool, u32 recordId);
extern int MapFieldSlotIndex(int slot);
extern int CountAssignedFieldSlots(void);
extern void func_ov027_020b8200(void *pool, void *record, s16 y);
extern void func_ov027_020b8230(void *pool, void *record);

void SetFieldSlotHudRecord(int slot, int kind, BOOL useKind)
{
    FieldSlotRecordIds ids = gFieldSlotHudRecordIds;
    int *recordIds = ids.ids;

    if (IsHudFlag9Set()) {
        void *pool = GetSceneTagTracker();
        void *record;

        if (useKind) {
            record = FindActiveRecordById(pool, (u16)recordIds[kind]);
        } else {
            record = FindActiveRecordById(pool, 570);
        }

        int index = MapFieldSlotIndex(slot);
        FieldSlotHud *manager = data_ov001_020a04c4.manager;

        if (manager->slotLabelsDirty || data_0205fde4) {
            manager->slotRecords[index] = record;
            return;
        }

        int top = 22 - CountAssignedFieldSlots() * 2 + index * 2;
        func_ov027_020b8200(pool, record, (s16)top);
        func_ov027_020b8230(pool, record);
    }
}
