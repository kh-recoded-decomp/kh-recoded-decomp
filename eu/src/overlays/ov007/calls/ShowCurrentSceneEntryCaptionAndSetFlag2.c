#include "nitro/types.h"

#define func_ov001_020681d4 GetSceneEntryResourceId

extern int GetCurrentSceneEntryIndex(void);
extern int func_ov001_020681d4(void);
extern int SetFieldCaptionText(void);

typedef struct {
    u8 pad_00[0x0F];
    u8 flags;
} UnkObj_020a0884;

s32 ShowCurrentSceneEntryCaptionAndSetFlag2(u32 unused, UnkObj_020a0884 *obj)
{
    obj->flags |= 2;
    GetCurrentSceneEntryIndex();
    func_ov001_020681d4();
    SetFieldCaptionText();
    return 0;
}
