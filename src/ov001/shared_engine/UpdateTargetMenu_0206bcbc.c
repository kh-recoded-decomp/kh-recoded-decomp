#include "nitro/types.h"

typedef struct TargetMenu {
    u32 flags;
    int state;
} TargetMenu;

extern TargetMenu *data_ov001_020a0484;
extern void func_ov001_0206bd30(int mode);
extern BOOL func_ov001_0206b06c(void);
extern void func_ov001_0206bb74(int first, int second);
extern int UpdateSubModeResult_020af46c(void);
extern u32 func_ov001_02072040(void);
extern BOOL func_ov001_020645c8(u32 value);
extern void SelectNearestTarget_0206afec(void);

void UpdateTargetMenu_0206bcbc(void)
{
    TargetMenu *menu = data_ov001_020a0484;

    if (menu->flags & 2) {
        func_ov001_0206bd30(0);
        if ((menu->flags & 2) && func_ov001_0206b06c()) {
            func_ov001_0206bb74(1, 1);
        }
    } else if (!UpdateSubModeResult_020af46c()) {
        func_ov001_0206bd30(1);
    }
    if (!(menu->flags & 2) && menu->state == 1 && func_ov001_02072040()
        && !func_ov001_020645c8(0x3609) && !func_ov001_020645c8(0x360a)) {
        SelectNearestTarget_0206afec();
    }
}
