#include "nitro/types.h"

typedef struct {
    u8 pad_00[6];
    s8 selected;
    u8 pad_07[0x138 - 7];
} StageData;

typedef struct {
    u16 stageId;
} StageStartParams;

extern StageData *data_ov001_020a0470;
extern void *NNSi_FndAllocFromDefaultHeap_0202a178(u32 size);
extern void func_01ff8740(u32 value, void *dst, u32 size);
extern void StageEvents_StartIfIdle_0208765c(void *userData);
extern int AcquireRecordSlot_02051d3c(int slot, int param);

void CreateStageDataAndStart_02068568(u16 stageId) {
    StageStartParams params;
    data_ov001_020a0470 = NNSi_FndAllocFromDefaultHeap_0202a178(sizeof(StageData));
    func_01ff8740(0, data_ov001_020a0470, sizeof(StageData));
    data_ov001_020a0470->selected = -1;
    params.stageId = stageId;
    StageEvents_StartIfIdle_0208765c(&params);
    AcquireRecordSlot_02051d3c(4, 0);
}
