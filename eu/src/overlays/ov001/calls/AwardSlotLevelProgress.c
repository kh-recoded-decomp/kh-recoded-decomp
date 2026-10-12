#include "nitro/types.h"
#include "nitro/fx.h"

typedef struct ProgressSave {
    u8 reserved0000[0x28cc];
    u32 experience;
} ProgressSave;

typedef struct ProgressRecord {
    u16 kind : 2;
    u16 reserved00 : 14;
    u16 active : 1;
    u16 level : 7;
    u16 category : 8;
} ProgressRecord;

extern ProgressSave *data_0205fe0c;
extern void *GetOverlaySelectionRecord(u32 index);
extern fx32 HalveForEachFlag(void);
extern fx32 CountUnlockedSlotsFx(void);
extern fx32 FX_Sqrt(fx32 value);
extern fx32 FX_Mul(fx32 a, fx32 b);
extern BOOL ResolveRecordHandle(int slot, ProgressRecord *record, u32 *handle);
extern BOOL AddSlotLevelProgress(int slot, u32 amount);
extern ProgressRecord *GetActiveRecordEntryOrNull(int index);
/* The original caller also supplies kind and level; this callee uses index. */
extern void FormatChoiceValueText(int index, ...);

#pragma opt_propagation off
static inline ProgressRecord *FindCategoryRecord(int category)
{
    return GetActiveRecordEntryOrNull((u16)category);
}
#pragma opt_propagation on

void AwardSlotLevelProgress(int amount)
{
    int slot;
    int progress;
    fx32 factor;
    ProgressRecord record;
    u32 handle;

    GetOverlaySelectionRecord(0);
    if (amount != 0) {
        int weighted = amount * HalveForEachFlag();
        ProgressSave *save = data_0205fe0c;
        save->experience += weighted >> 12;
        if (data_0205fe0c->experience > 99999999) {
            data_0205fe0c->experience = 99999999;
        }
        factor = FX_Mul(0x800, FX_Sqrt(amount << 12)) + 0x2000;
        factor = CountUnlockedSlotsFx() * (factor >> 12);
        slot = 0;
        progress = factor >> 12;
        for (; slot < 16; ++slot) {
            if (ResolveRecordHandle(slot, &record, &handle) &&
                AddSlotLevelProgress(slot, progress)) {
                u16 category = (u8)record.category;
                ProgressRecord *entry = FindCategoryRecord(category);
                if (entry != NULL) {
                    FormatChoiceValueText(category, (s8)entry->kind, (s8)entry->level);
                }
            }
        }
    }
}
