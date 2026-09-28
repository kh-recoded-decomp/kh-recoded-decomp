#include "nitro/types.h"

typedef struct {
    u32 id;
    u8 pad_004[0x104];
} ListEntry;

typedef struct {
    u32 unk_00;
    int cursor;
    u8 pad_008[0x110];
    ListEntry entries[1];
} EntryList;

extern void *func_ov039_020bc1bc(void);
extern BOOL func_ov087_020c7c18(u32 entryId);
extern void func_ov027_020b9874(void *container, BOOL enable);
extern void SetPrimaryElementEnabled_020bc054(BOOL enabled);
extern void SetSecondaryElementEnabled_020bc084(BOOL enabled);
extern BOOL PlaySoundEffect_0204d924(int seqArcNo, int index);

void SwitchToSecondaryIfEntryRejected_020c4684(EntryList *list)
{
    void *container = func_ov039_020bc1bc();

    if (func_ov087_020c7c18(list->entries[list->cursor].id)) {
        return;
    }
    func_ov027_020b9874(container, FALSE);
    SetPrimaryElementEnabled_020bc054(FALSE);
    SetSecondaryElementEnabled_020bc084(TRUE);
    PlaySoundEffect_0204d924(0, 2);
}
