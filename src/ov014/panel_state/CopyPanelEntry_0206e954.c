#include "nitro/types.h"

extern u32 g_panelState_0206f9a0;
extern void func_ov027_020b9360(u32 panel, u32 value, void *buffer, s32 flag);
extern u32 func_ov027_020b90a4(u32 panel, u32 value);
extern void func_ov027_020b91c8(u32 panel, u32 value, void *buffer, s32 flag);

void CopyPanelEntry_0206e954(u32 entryId)
{
    u32 buffer[2];
    u32 slot;

    func_ov027_020b9360(g_panelState_0206f9a0 + 0x6514, entryId, buffer, 0);
    slot = func_ov027_020b90a4(g_panelState_0206f9a0 + 0x6514, 0);
    func_ov027_020b91c8(g_panelState_0206f9a0 + 0x6514, slot, buffer, 0);
}
