#include "nitro/types.h"

typedef struct {
    u8 pad_000[0xc];
    u8 handlerContext[0x168];
    u8 flagTracker[0x1c];
} Ov086Menu;

extern void CallVirtualHandlerSlot1_02001574(void *context, int arg);
extern void func_ov039_020bc104(int elementId);
extern void func_ov027_020b9e00(u8 *tracker, int id);
extern void func_ov086_020bf9d4(Ov086Menu *menu, int slot);

void func_ov086_020bfb80(Ov086Menu *menu)
{
    CallVirtualHandlerSlot1_02001574(menu->handlerContext, 0);
    func_ov039_020bc104(0x18);
    func_ov027_020b9e00(menu->flagTracker, 0x19);
    func_ov086_020bf9d4(menu, 0);
    func_ov086_020bf9d4(menu, 1);
    func_ov086_020bf9d4(menu, 2);
    func_ov086_020bf9d4(menu, 3);
}
