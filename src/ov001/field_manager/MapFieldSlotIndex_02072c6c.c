#include "nitro/types.h"

typedef struct SlotMap {
    int slots[3];
} SlotMap;

extern const SlotMap data_ov001_0209dba0;
extern int CountAssignedFieldSlots_0207169c(void);

int MapFieldSlotIndex_02072c6c(int index)
{
    SlotMap map = data_ov001_0209dba0;

    if (CountAssignedFieldSlots_0207169c() > 0) {
        index = map.slots[index];
    }
    return index;
}
