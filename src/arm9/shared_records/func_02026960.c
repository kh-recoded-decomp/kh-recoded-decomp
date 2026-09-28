#include "nitro/types.h"

typedef struct {
    u8 pad_000[0x1c8];
    void *entry;
} HandlerTable;

extern int func_0202c438(void);
extern int ReleaseSharedRecordSlot_0202c8a8(void *slot);

void func_02026960(HandlerTable *table, s32 index)
{
    if (index >= 0) {
        func_0202c438();
        ReleaseSharedRecordSlot_0202c8a8(*(void **)((u8 *)table->entry + 8));
    }
}
