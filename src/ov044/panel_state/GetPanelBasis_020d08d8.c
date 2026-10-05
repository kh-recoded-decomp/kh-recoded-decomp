#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    VecFx32 axes[3];
} Basis;

extern u32 g_panel_020d0ea0;

extern void BuildBasisFromForward_0204bf70(const VecFx32 *forward, const VecFx32 *up, Basis *basis);

void GetPanelBasis_020d08d8(Basis *out)
{
    Basis built;
    Basis basis;

    BuildBasisFromForward_0204bf70((VecFx32 *)(g_panel_020d0ea0 + 0x70), (VecFx32 *)(g_panel_020d0ea0 + 0x7c), &built);
    basis = built;
    *(Basis *)out = *(Basis *)&basis;
}
