#include "nitro/types.h"

extern u32 *data_ov023_020b6f84;
extern u8 data_ov023_020b6efc;
extern u32 SetSlotAnimSequence();
extern u32 IndexedRecords_SetFlag2();
extern u32 SetPanelSessionActive();
extern u32 ClearPanelSessionActive();
extern u32 RequestPanelFallback();
extern u32 QueueFileLoadRequest();
extern void ApplyMenuScreenEntry(void);

void PrepareMenuScreenEntry(u32 index, u32 value)
{
    u32 *work;
    u32 mode;
    int resourceIndex;
    u32 *base;

    work = data_ov023_020b6f84;
    *data_ov023_020b6f84 = index;
    work[1] = value;
    base = work + 0x16;
    SetSlotAnimSequence(base, work[0x1923], work[8] != 1);
    IndexedRecords_SetFlag2(base, work[0x1924], 1);
    resourceIndex = 0;
    do {
        mode = 4;
        if (work[8] != 1) {
            mode = 5;
        }
        SetSlotAnimSequence(base, work[resourceIndex + 0x1925], mode);
        resourceIndex = resourceIndex + 1;
    } while (resourceIndex < 2);
    work[0xd] = 0;
    if (index >= 8) {
        SetPanelSessionActive();
        RequestPanelFallback();
        return;
    }
    ClearPanelSessionActive();
    QueueFileLoadRequest(
        ((work[2] + 0x8000 & 0xfffffc) << 7) |
            0x80000000 |
            (*(u16 *)(&data_ov023_020b6efc + index * 2) & 0x1ff),
        1,
        (u32)ApplyMenuScreenEntry,
        0
    );
}
