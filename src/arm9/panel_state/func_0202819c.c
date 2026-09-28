#include "nitro/types.h"

typedef struct PanelState {
    u8 pad_00[0xb8];
    s32 field_b8;
} PanelState;

extern PanelState *g_ptr_0205fe24;
extern void func_02025464(int mode);

void func_0202819c(void)
{
    g_ptr_0205fe24->field_b8 = 0;
    func_02025464(2);
}
