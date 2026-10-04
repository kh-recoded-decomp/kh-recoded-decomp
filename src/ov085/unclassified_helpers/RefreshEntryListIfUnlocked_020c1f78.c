#include "nitro/types.h"

typedef struct EntryList {
    u8 pad_0000[0x4582];
    u8 locked;
} EntryList;

extern void func_ov085_020c1974(EntryList *list);

void RefreshEntryListIfUnlocked_020c1f78(EntryList *list)
{
    if (list->locked == 0) {
        func_ov085_020c1974(list);
    }
}
