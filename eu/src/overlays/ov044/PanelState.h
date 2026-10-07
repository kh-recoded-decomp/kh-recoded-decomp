#ifndef KH_RECODED_OV044_PANEL_STATE_H
#define KH_RECODED_OV044_PANEL_STATE_H

#include "nitro/fx_types.h"
#include "nitro/types.h"

typedef struct PanelState {
    u8 pad_000[0x70];
    VecFx32 driftOrigin;
    u8 pad_07c[0x60];
    u8 activeController;
    u8 pad_0dd[0x87];
    u8 viewState;
} PanelState;

extern PanelState *data_ov044_020d0ec0;

#endif
