#include "nitro/types.h"

typedef struct StageData {
    u8 pad_00000[0x18f44];
    int score;
    u16 scoringEnabled;
} StageData;

extern StageData *data_ov001_020a0508;

void AddStageScore_0209cdc4(int kind)
{
    StageData *stage = data_ov001_020a0508;
    int amount = 0;

    if (stage->scoringEnabled == 0) {
        return;
    }
    switch (kind) {
    case 0:
        amount = 1;
        break;
    case 1:
        amount = 10;
        break;
    case 2:
        amount = 100;
        break;
    }
    stage->score += amount;
    if (data_ov001_020a0508->score < 0) {
        data_ov001_020a0508->score = 0;
    }
}
