#include "src/overlays/ov001/FieldUiTables.h"

extern const u8 gMenuResourceCacheTaskClass[];
extern const u8 data_ov024_020b74a0[];
extern const u8 gMenuListTaskClass[];
extern const u8 gOverlayDisplaySessionTaskClass[];

PanelModeDataTable gPanelModeDataPointers = {{
    gMenuResourceCacheTaskClass,
    data_ov024_020b74a0,
    gMenuListTaskClass,
    gMenuResourceCacheTaskClass,
    gOverlayDisplaySessionTaskClass,
}};
