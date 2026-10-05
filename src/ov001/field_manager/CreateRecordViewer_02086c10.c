#include "nitro/types.h"

typedef struct RecordViewer {
    u8 pad_000[0x64];
    u8 records[0xce];
    s16 selectedId;
    s8 selectedSlot;
    u8 pad_135[0x1c8 - 0x135];
} RecordViewer;

extern RecordViewer *data_ov001_020a04dc;
extern void *NNSi_FndAllocFromDefaultHeap_0202a178(u32 size);
extern void func_01ff8740(u32 value, void *dest, u32 size);
extern void func_01ff89a8(const void *src, void *dest, u32 size);
extern void AcquireRecordSlot_02051d3c(int slot, int mode);
extern void *GetRecordTableEPointer_020522a0(void);
extern void ReleaseRecordSlot_02051dfc(int slot);

void CreateRecordViewer_02086c10(void)
{
    data_ov001_020a04dc = NNSi_FndAllocFromDefaultHeap_0202a178(sizeof(RecordViewer));
    func_01ff8740(0, data_ov001_020a04dc, sizeof(RecordViewer));
    data_ov001_020a04dc->selectedId = -1;
    data_ov001_020a04dc->selectedSlot = -1;
    AcquireRecordSlot_02051d3c(12, 1);
    func_01ff89a8(GetRecordTableEPointer_020522a0(), data_ov001_020a04dc->records, sizeof(data_ov001_020a04dc->records));
    ReleaseRecordSlot_02051dfc(12);
}

