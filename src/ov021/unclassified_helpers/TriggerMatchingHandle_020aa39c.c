#include "nitro/types.h"

typedef struct HandleOwner {
    u8 pad0[2];
    u8 kind;
} HandleOwner;

typedef struct HandleEntry {
    HandleOwner *owner;
    int pad4;
    int key;
} HandleEntry;

typedef struct HandleGroup {
    HandleEntry *entries;
    HandleEntry *altEntries;
    int count;
    int altCount;
    u8 pad10[0x10];
} HandleGroup;

typedef struct HandleBank {
    u8 pad0[0xc];
    HandleGroup groups[2];
    u8 pad4c[0x14];
    HandleEntry *active;
} HandleBank;

extern BOOL IsObjHandleRequirementMet_020aa4f0(HandleBank *bank, int group);
extern void BeginObjHandleCheck_020aa40c(HandleBank *bank, HandleEntry *entry, int group);

BOOL TriggerMatchingHandle_020aa39c(HandleBank *bank, int key, int group)
{
    int i;
    HandleEntry *entry;
    HandleEntry *entries;
    int count;
    HandleGroup *handles;
    BOOL found = FALSE;
    HandleGroup *groups = bank->groups;

    handles = &groups[group];
    entries = groups[group].entries;
    count = handles->count;

    if (IsObjHandleRequirementMet_020aa4f0(bank, group)) {
        entries = handles->altEntries;
        count = handles->altCount;
    }
    for (i = 0; i < count; i++) {
        entry = &entries[i];
        if (key == entry->key && (bank->active == NULL || bank->active->owner->kind != entry->owner->kind)) {
            BeginObjHandleCheck_020aa40c(bank, entry, group);
            found = TRUE;
            break;
        }
    }
    return found;
}
