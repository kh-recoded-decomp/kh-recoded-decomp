#include "nitro/types.h"

typedef struct {
    int flagIds[3];
} FlagIdTable;

extern const FlagIdTable data_ov086_020c20dc;
extern BOOL func_ov001_020645c8(u32 flagId);

int GetHighestSetFlagTier_020bf658(int baseFlagId)
{
    FlagIdTable table = data_ov086_020c20dc;
    int i;
    int lastSet = -1;

    for (i = 0; i < 3; i++) {
        if (func_ov001_020645c8(baseFlagId + table.flagIds[i])) {
            lastSet = i;
        }
    }
    return lastSet + 1;
}
