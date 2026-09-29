#include "nitro/types.h"

typedef struct EntryList {
    u8 pad_0000[0x4580];
    u16 filteredCount;
} EntryList;

extern void func_ov085_020c1dcc(EntryList *list, const u32 *categories, u32 categoryCount, BOOL exclude);

u16 FilterEntriesByCategorySet_020c1fa0(EntryList *list, const u32 *categories, u32 categoryCount, BOOL exclude) {
    func_ov085_020c1dcc(list, categories, categoryCount, exclude);
    return list->filteredCount;
}
