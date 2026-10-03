#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct EventTargetInfo {
    u16 id;
    u16 isPartner : 1;
    u16 rest : 15;
    u16 kind;
    u16 pad_06;
    VecFx32 position;
    s32 width;
    s32 height;
    s32 displayWidth;
    s32 displayHeight;
} EventTargetInfo;

typedef struct RewardSource {
    union {
        u32 kind;
        u16 eventId;
    } id;
    int type;
} RewardSource;

extern int GetKindDuration_020a37c4(u32 kind);
extern int StageRecord_GetLinkedEntryValue_02087cf0(u16 id);
extern void GetStageEventTargetInfo_02087960(u16 id, EventTargetInfo *info);
extern void AddSessionCounter_02063a80(int counter, int value);
extern void SpawnRewardOrbs_02066514(u16 *amounts, VecFx32 *pos, u32 arg);
extern void func_ov059_020cf0a4(VecFx32 *out, RewardSource *src);

void SpawnSourceRewardOrbs_020cd3c4(RewardSource *src, int multiplier, int counter) {
    EventTargetInfo info;
    int amount;

    switch (src->type) {
    case 1:
        amount = GetKindDuration_020a37c4(src->id.kind);
        break;
    case 2:
        amount = StageRecord_GetLinkedEntryValue_02087cf0(src->id.eventId);
        GetStageEventTargetInfo_02087960(src->id.eventId, &info);
        if (info.isPartner) {
            AddSessionCounter_02063a80(counter, amount);
            return;
        }
        break;
    }
    if (multiplier >= 2) {
        amount = amount * multiplier;
    }
    if (amount != 0) {
        u16 amounts[6] = {0, 0, 0, 0, 0, 0};
        VecFx32 pos;
        amounts[2] = amount / 10;
        func_ov059_020cf0a4(&pos, src);
        SpawnRewardOrbs_02066514(amounts, &pos, 0);
    }
}
