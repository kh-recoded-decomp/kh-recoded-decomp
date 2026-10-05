#include "nitro/types.h"

typedef struct StageData {
    u8 pad_00000[0x18f44];
    int score;
    u16 scoreEventId;
} StageData;

typedef struct StageEventRecord {
    u8 pad_00[0xe];
    u16 type;
    u16 actorId;
} StageEventRecord;

typedef struct StageActor {
    u8 pad_000[0x2c0];
    u8 position[0xc];
} StageActor;

typedef struct ScorePopup {
    u16 unk_00;
    u16 unk_02;
    u16 unk_04;
    u16 unk_06;
    u16 value;
    u16 unk_0A;
} ScorePopup;

extern StageData *data_ov001_020a0508;
extern StageEventRecord *GetStageEventRecord_0209c0ec(u32 id);
extern StageActor *GetStageActor_0209c040(int id);
extern void SpawnRewardOrbs_02066514(ScorePopup *popup, void *position, int flags);

void FinishScoreEvent_0209ce10(StageEventRecord *expected)
{
    StageEventRecord *record;
    StageActor *actor;

    if (data_ov001_020a0508->scoreEventId == 0) {
        return;
    }
    record = GetStageEventRecord_0209c0ec(data_ov001_020a0508->scoreEventId);
    if (record == NULL || record != expected || record->actorId == 0 || record->type != 0x3f) {
        return;
    }
    actor = GetStageActor_0209c040((s16)record->actorId);
    if (actor == NULL) {
        return;
    }
    {
        ScorePopup popup = {0, 0, 0, 0, 0, 0};

        popup.value = data_ov001_020a0508->score + 999;
        SpawnRewardOrbs_02066514(&popup, actor->position, 0);
    }
    data_ov001_020a0508->scoreEventId = 0;
    data_ov001_020a0508->score = 0;
}
