#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x48];
    u32 unk_48;
} OverlayState;

extern OverlayState *g_activeState_020bc800;
extern u32 GetCtxModeByte_02068084(void);
extern void func_ov001_0206459c(u32 messageId, u32 severity, u32 code);

void ReportContextError_020bc524(u32 code)
{
    u32 result;
    u32 messageId;

    g_activeState_020bc800->unk_48 = code;
    result = GetCtxModeByte_02068084();
    if (result == 2) {
        messageId = 0x3710;
    } else {
        messageId = 0x3718;
    }
    func_ov001_0206459c(messageId, 6, code);
}
