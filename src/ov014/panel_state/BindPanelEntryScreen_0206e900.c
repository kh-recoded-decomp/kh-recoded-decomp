#include "nitro/types.h"

extern u32 g_panelState_0206f9a0;
extern void *G2S_GetBG0ScrPtr_02006e14(void);
extern void func_ov027_020b9b18(u32 panel, u32 entryId, void *scrPtr);

void BindPanelEntryScreen_0206e900(u32 entryId)
{
    void *scrPtr = G2S_GetBG0ScrPtr_02006e14();
    func_ov027_020b9b18(g_panelState_0206f9a0 + 0xc990, entryId, scrPtr);
}
