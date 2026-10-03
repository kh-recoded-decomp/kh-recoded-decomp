#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u32 words[6];
} PanelTransition;

extern u32 g_panel_020d0ea0;
extern PanelTransition data_ov044_020d0e80;

extern void func_ov044_020d0200(void);

void StartPanelTransition_020d02c0(const PanelTransition *transition, const VecFx32 *target, u32 data)
{
    *(u32 *)(g_panel_020d0ea0 + 0x44) = 6;
    *(u32 *)(g_panel_020d0ea0 + 0x64) = 0;
    *(u32 *)(g_panel_020d0ea0 + 0x68) = data;
    *(u32 *)(g_panel_020d0ea0 + 0x6c) = 1;
    *(VecFx32 *)(g_panel_020d0ea0 + 0xd0) = *target;
    data_ov044_020d0e80 = *transition;
    func_ov044_020d0200();
}
