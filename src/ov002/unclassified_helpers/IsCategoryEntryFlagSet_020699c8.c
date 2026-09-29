#include "nitro/types.h"

extern s32 func_ov002_02069dd8(s32 category, s32 entryIndex);
extern BOOL func_ov002_0206991c(s32 recordId);

BOOL IsCategoryEntryFlagSet_020699c8(s32 category, s32 entryIndex) {
    s32 recordId = func_ov002_02069dd8(category, entryIndex);
    if (entryIndex < 0) {
        return FALSE;
    }
    return func_ov002_0206991c(recordId);
}
