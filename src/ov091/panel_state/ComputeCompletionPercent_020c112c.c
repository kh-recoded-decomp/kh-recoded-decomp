#include "nitro/types.h"

typedef struct {
    int kind;
    int value;
} Requirement;

typedef struct {
    u8 pad_00[0xc9f8];
    int completionPercent;
} EntryScene;

extern const Requirement data_ov091_020c2de8[];
extern BOOL IsGlobalPackedBitSet_02027304(int bitIndex);
extern int func_02051270(int slot);

void ComputeCompletionPercent_020c112c(EntryScene *scene)
{
    int count = 0;
    int owned[32];
    int ownedCount = 0;
    int n;

    for (n = 0; n < 32; n++) {
        int item = func_02051270(n);
        if (item != -1) {
            owned[ownedCount] = item;
            ownedCount++;
        }
    }
    for (n = 0; n < 239; n++) {
        const Requirement *req = &data_ov091_020c2de8[n];
        int bit;
        switch (req->kind) {
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
        case 7:
        case 8:
            bit = req->value;
            break;
        case 5: {
            int k;
            for (k = 0; k < ownedCount; k++) {
                if (req->value == owned[k]) {
                    count++;
                    break;
                }
            }
            continue;
        }
        case 6:
            switch (req->value) {
            case 6:
                bit = 0xbeb;
                break;
            case 8:
                bit = 0xbec;
                break;
            case 10:
                bit = 0xbed;
                break;
            case 12:
                bit = 0xbee;
                break;
            case 14:
                bit = 0xbef;
                break;
            default:
                continue;
            }
            break;
        default:
            continue;
        }
        if (IsGlobalPackedBitSet_02027304(bit)) {
            count++;
        }
    }
    scene->completionPercent = count * 100 / 239;
}
