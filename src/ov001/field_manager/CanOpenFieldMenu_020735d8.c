#include "nitro/types.h"

typedef struct Hud {
    u8 pad_000[0x47c];
    s32 busy;
} Hud;

typedef struct HudHandle {
    u32 unk_00;
    Hud *hud;
} HudHandle;

extern HudHandle data_ov001_020a04a4;

extern BOOL IsSessionIdleForSceneChange_020638ec(void);
extern BOOL IsHudFlag7Set_020725bc(void);
extern BOOL IsFieldFlag10Set_020728c4(void);
extern BOOL IsFieldFlag8Set_020728a4(void);
extern int func_ov001_02064784(void);
extern BOOL func_ov001_020645c8(u32 value);

BOOL CanOpenFieldMenu_020735d8(void)
{
    BOOL result = TRUE;

    if (!IsSessionIdleForSceneChange_020638ec()) {
        result = FALSE;
    }
    if (data_ov001_020a04a4.hud->busy != 0) {
        result = FALSE;
    }
    if (IsHudFlag7Set_020725bc() || IsFieldFlag10Set_020728c4() || IsFieldFlag8Set_020728a4()) {
        result = FALSE;
    }
    if (!func_ov001_02064784() && func_ov001_020645c8(0x370b)) {
        result = FALSE;
    }
    return result;
}
