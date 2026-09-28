#include "nitro/types.h"

typedef struct {
    int id;
    u8 pad_0004[0x0c];
    int next;
} Ov039ListEntry;

extern int data_ov039_020bea00;
extern void *NNSi_FndAllocFromDefaultHeap_0202a178(u32 size);
extern void func_01ff8830(void *dst, int value, u32 size);
extern void AppendIntrusiveListObject_020128d0(char *list, char *obj);

Ov039ListEntry *AllocateListEntry_020bc6b0(int id)
{
    Ov039ListEntry *entry;

    if (id == 0) {
        return 0;
    }
    entry = (Ov039ListEntry *)NNSi_FndAllocFromDefaultHeap_0202a178(sizeof(Ov039ListEntry));
    func_01ff8830(entry, 0, sizeof(Ov039ListEntry));
    entry->id = id;
    entry->next = 0;
    AppendIntrusiveListObject_020128d0((char *)(data_ov039_020bea00 + 0xca74), (char *)entry);
    return entry;
}
