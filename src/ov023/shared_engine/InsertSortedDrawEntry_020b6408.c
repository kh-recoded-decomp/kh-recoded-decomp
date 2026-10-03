#include "nitro/types.h"

typedef struct DrawEntry {
    u8 pad_00[0x14];
    s32 priority;
    u8 pad_18[0x4];
    u8 subPriority;
} DrawEntry;

extern DrawEntry *NNS_FndGetNextListObject_02012a38(void *list, DrawEntry *obj);
extern void InsertIntrusiveListObject_02012974(void *list, DrawEntry *before, DrawEntry *obj);
extern void AppendIntrusiveListObject_020128d0(void *list, DrawEntry *obj);

void InsertSortedDrawEntry_020b6408(u8 *owner, DrawEntry *entry, s32 priority, int subPriority)
{
    DrawEntry *obj = NNS_FndGetNextListObject_02012a38(owner + 0x6874, NULL);

    while (obj != NULL) {
        if (obj->priority >= priority && (obj->priority != priority || obj->subPriority >= subPriority)) {
            InsertIntrusiveListObject_02012974(owner + 0x6874, obj, entry);
            break;
        }
        obj = NNS_FndGetNextListObject_02012a38(owner + 0x6874, obj);
    }
    if (obj == NULL) {
        AppendIntrusiveListObject_020128d0(owner + 0x6874, entry);
    }
}
