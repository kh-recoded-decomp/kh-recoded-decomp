#include "nitro/types.h"

typedef struct PanelState {
    u8 pad_00[0x64];
    u32 resourceId;
    u8 pad_68[0x18];
} PanelState;

extern PanelState *g_ptr_0205fe24;
extern u32 func_0202c478(u32 fileId, u32 param2, u32 param3, u32 param4);
extern void func_0202b554(void *view, u32 resource, int a, int b, int c);
extern void *AllocAndRegisterOrFree_0202b504(int this_, int arg1, int arg2);
extern u8 data_02055f64[];
extern u8 data_02055f7c[];
extern u8 data_02055f94[];

void func_020282bc(int param1, int param2, u32 param3, u32 param4)
{
    PanelState *panel = g_ptr_0205fe24;
    panel->resourceId = func_0202c478((u32)data_02055f64, 0x11, param3, param4);
    func_0202b554((u8 *)panel + 0x68, panel->resourceId, 0, 0, 0);
    *(void **)((u8 *)panel + 0x10) = AllocAndRegisterOrFree_0202b504((int)((u8 *)panel + 0x18), (int)data_02055f7c, 0x11);
    *(void **)((u8 *)panel + 0xc) = AllocAndRegisterOrFree_0202b504((int)((u8 *)panel + 0x14), (int)data_02055f94, 0x11);
}
