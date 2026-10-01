#include "nitro/types.h"

extern const s8 data_ov001_020a038c[];
extern int func_ov001_020644b0(void);
extern s32 func_ov032_020bb808(void);
extern BOOL func_ov032_020bb840(int groupId);
extern u32 GetGroupIndexedValue_020bb86c(u32 index);

u32 RemapGroupMemberId_0209cfcc(u32 memberId, int groupId, BOOL skipLookup)
{
    BOOL inSpecialScene = (func_ov001_020644b0() == 900) ? TRUE : FALSE;

    if (inSpecialScene) {
        u8 available = TRUE;
        BOOL groupValid = TRUE;
        if (!skipLookup) {
            available = func_ov032_020bb808();
            if (groupId != 0xffff) {
                groupValid = func_ov032_020bb840(groupId);
            }
            memberId = GetGroupIndexedValue_020bb86c(memberId);
        }
        if (groupValid && available && memberId < 0x46) {
            s8 remapped = data_ov001_020a038c[memberId];
            if (remapped < 0) {
                remapped = memberId + 0x46;
            }
            memberId = (u16)remapped;
        }
    }
    return memberId;
}
