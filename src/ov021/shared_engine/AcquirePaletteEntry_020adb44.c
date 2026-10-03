#include "nitro/types.h"

typedef struct {
    u32 owner;
    int index;
    u32 active;
    u32 *state;
    u32 *altState;
    u8 pad_14[0xc];
} PaletteEntry;

extern void *NNSi_FndAllocFromDefaultHeap_0202a178(u32 size);
extern PaletteEntry *func_ov021_020acce8(void *manager, int index);
extern void SetPendingFromTable_020a9598(int index);
extern void ClearPendingWord_020a95b4(void);
extern u32 MakePaletteUploadParams210_020a963c(u32 index, u32 owner);
extern u32 MakePaletteUploadParams160_020a9664(u32 index, u32 owner);
extern int func_ov021_020a96dc(int index, u32 owner);
extern void AcquireSharedRecordState_020a9054(void *obj, s32 key, u32 initArg, u32 context);
extern void AppendIntrusiveListObject_020128d0(void *list, void *obj);

PaletteEntry *AcquirePaletteEntry_020adb44(u8 *manager, u8 *scene, int index, u32 owner) {
    u8 *record = *(u8 **)(scene + 0xc);
    u32 altArg = *(u32 *)(record + 0x228);
    u32 context = *(u32 *)(manager + 0x14) + 8;
    BOOL high = index >= 15;
    PaletteEntry *entry = func_ov021_020acce8(manager, index);
    s32 key;
    if (entry == NULL) {
        entry = NNSi_FndAllocFromDefaultHeap_0202a178(sizeof(PaletteEntry));
        entry->index = index;
        entry->owner = owner;
        SetPendingFromTable_020a9598(0);
        if (high) {
            index -= 15;
            key = MakePaletteUploadParams160_020a9664(index, owner);
        } else {
            key = MakePaletteUploadParams210_020a963c(index, owner);
        }
        entry->state = NNSi_FndAllocFromDefaultHeap_0202a178(0x2c);
        *entry->state = 0;
        AcquireSharedRecordState_020a9054(entry->state, key, (u32)(record + 8), context);
        if (altArg != 0 && high) {
            int altKey = func_ov021_020a96dc(index, owner);
            entry->altState = NULL;
            if (altKey != 0) {
                entry->altState = NNSi_FndAllocFromDefaultHeap_0202a178(0x2c);
                *entry->altState = 0;
                AcquireSharedRecordState_020a9054(entry->altState, altKey, altArg, context);
            }
        } else {
            entry->altState = NULL;
        }
        ClearPendingWord_020a95b4();
        entry->active = 1;
        AppendIntrusiveListObject_020128d0(manager + 0x58, entry);
    }
    return entry;
}
