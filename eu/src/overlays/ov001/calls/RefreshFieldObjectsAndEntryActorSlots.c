#include "nitro/types.h"

extern u32 data_ov001_020a04f8;
extern void FieldObject_Refresh(void *node);
extern void ApplyActorSlotsToFieldEntryList(void);

void RefreshFieldObjectsAndEntryActorSlots(void)
{
    u8 *node;

    for (node = *(u8 **)(data_ov001_020a04f8 + 8); node != 0; node = *(u8 **)(node + 4)) {
        FieldObject_Refresh(node);
    }
    ApplyActorSlotsToFieldEntryList();
}
