#include "nitro/types.h"

extern u32 gFieldObjectClassManager;
extern void FieldObject_Refresh(void *node);
extern void ApplyActorSlotsToFieldEntryList(void);

void RefreshFieldObjectsAndEntryActorSlots(void)
{
    u8 *node;

    for (node = *(u8 **)(gFieldObjectClassManager + 8); node != 0; node = *(u8 **)(node + 4)) {
        FieldObject_Refresh(node);
    }
    ApplyActorSlotsToFieldEntryList();
}
