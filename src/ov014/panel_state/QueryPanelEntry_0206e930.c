#include "nitro/types.h"

extern u32 g_panelState_0206f9a0;
extern int func_ov027_020b9b94(u32 panel, int entryId);

int QueryPanelEntry_0206e930(int entryId)
{
    return func_ov027_020b9b94(g_panelState_0206f9a0 + 0xc990, entryId);
}
