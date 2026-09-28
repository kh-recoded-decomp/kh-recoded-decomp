#include "nitro/types.h"

typedef struct {
    void *file;
    u32 count;
    u8 *strings;
} MessageSet;

typedef struct {
    u8 pad_00[0x1c];
    u16 *name;
    MessageSet messages;
} ModeState;

typedef struct {
    u8 pad_000[0x130];
    s16 slotIndex;
} OverlaySelectionRecord;

typedef struct {
    u8 pad_00[0x28];
    u16 *name;
} SlotEntry;

extern u16 data_ov001_0209ef68[];

extern OverlaySelectionRecord *GetOverlaySelectionRecord_0204f768(u32 selectionIndex);
extern SlotEntry *GetRecordSlotPair1Entry_02051ef4(s32 index);
extern void *NNSi_FndAllocFromDefaultHeap_0202a178(u32 size);
extern int LengthTerminatedHalfwords_02022a38(u16 *text);
extern u16 *copy_padded_utf16_string_02022a74(u16 *destination, u16 *source, int unitCount);
extern u32 func_ov001_02073634(u32 messageId);
extern void func_ov027_020ba25c(MessageSet *messages, u32 fileId, int compressed);

void LoadModeNameAndMessages_0207ab10(ModeState *state)
{
    SlotEntry *entry = GetRecordSlotPair1Entry_02051ef4(GetOverlaySelectionRecord_0204f768(0)->slotIndex);

    if (entry == NULL) {
        state->name = NNSi_FndAllocFromDefaultHeap_0202a178(4);
        copy_padded_utf16_string_02022a74(state->name, data_ov001_0209ef68, 2);
    } else {
        int length = LengthTerminatedHalfwords_02022a38(entry->name) + 1;
        state->name = NNSi_FndAllocFromDefaultHeap_0202a178(length * 2);
        copy_padded_utf16_string_02022a74(state->name, entry->name, length);
    }
    func_ov027_020ba25c(&state->messages, func_ov001_02073634(8), 0);
}
