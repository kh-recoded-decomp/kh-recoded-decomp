#ifndef KH_RECODED_OV002_PANEL_STATE_H
#define KH_RECODED_OV002_PANEL_STATE_H

#include "nitro/types.h"
#include "nnsys/g2d.h"

typedef struct Ov002PanelFontResource {
    NNSG2dFont font;
    void *buffer;
} Ov002PanelFontResource;

typedef struct Ov002PanelTextLayer {
    u8 reserved00[0x34];
} Ov002PanelTextLayer;

typedef struct Ov002PanelMessageResource {
    void *file;
    u8 reserved04[8];
} Ov002PanelMessageResource;

typedef struct Ov002PanelState {
    u8 pad_000[0x10];
    u8 active : 1;
    u8 modeDirty : 1;
    u8 mainBg3TextInitialized : 1;
    u8 mainBg2TextInitialized : 1;
    u8 pad_10_bits : 4;
    u8 stateFlags;
    u8 keyRepeat[0x1e];
    Ov002PanelFontResource fonts[2];   /* 0x30 */
    Ov002PanelTextLayer textLayers[4]; /* 0x48 */
    Ov002PanelMessageResource messageFiles[2]; /* 0x118 */
} Ov002PanelState;

typedef char Ov002PanelStateSizeCheck[
    sizeof(Ov002PanelState) == 0x130 ? 1 : -1];

void ResetMainPanelGraphics(void);

extern Ov002PanelState *data_ov002_0206c460;
#define gOv002PanelState data_ov002_0206c460

#endif
