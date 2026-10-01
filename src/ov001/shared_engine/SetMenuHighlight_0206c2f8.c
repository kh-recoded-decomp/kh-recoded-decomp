#include "nitro/types.h"

typedef struct MenuContext {
    u32 flags;
} MenuContext;

extern MenuContext *data_ov001_020a0484;
extern void func_ov001_0206bb74(int first, int second);
extern void ResetPendingRequest_0206c614(void);

void SetMenuHighlight_0206c2f8(BOOL enable)
{
    MenuContext *menu = data_ov001_020a0484;

    if (menu != NULL) {
        if (enable) {
            menu->flags |= 4;
        } else {
            menu->flags &= ~4;
        }
        func_ov001_0206bb74(0, 0);
        ResetPendingRequest_0206c614();
    }
}
