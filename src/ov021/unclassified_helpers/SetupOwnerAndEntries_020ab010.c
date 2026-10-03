#include "nitro/types.h"

typedef struct Entry {
    u8 pad0[0x154];
} Entry;

typedef struct Owner {
    void *context;
    u8 pad04[4];
    Entry *entries;
    u8 pad0c[0x15 - 0xc];
    u8 count;
} Owner;

extern void func_ov021_020aa9c4(Owner *owner, int mode, int x, int y);
extern void func_ov021_020aaa6c(Entry *entry, void *context, int first, int second, int index);

void SetupOwnerAndEntries_020ab010(Owner *owner, int first, int second, int mode, int x, int y)
{
    int i;

    func_ov021_020aa9c4(owner, mode, x, y);
    for (i = 0; i < owner->count; i++) {
        func_ov021_020aaa6c(&owner->entries[i], owner->context, first, second, i);
    }
}
