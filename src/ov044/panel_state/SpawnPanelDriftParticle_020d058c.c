#include "nitro/types.h"
#include "nitro/fx_types.h"

extern u32 g_panel_020d0ea0;

extern VecFx32 *func_ov044_020d0578(void);
extern void InitDriftParticle_020afb34(void *particle, const VecFx32 *position, int param30, int param2c);

void SpawnPanelDriftParticle_020d058c(int param30, int param2c)
{
    InitDriftParticle_020afb34((void *)(g_panel_020d0ea0 + 0x110), func_ov044_020d0578(), param30, param2c);
}
