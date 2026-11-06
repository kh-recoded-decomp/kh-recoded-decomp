#include "src/overlays/ov001/FieldUiTables.h"

extern const u8 gMenuResourceCacheTaskClass[];
extern const u8 gBoardScreenTaskDescriptor[];
extern const u8 gMenuListTaskClass[];
extern const u8 gOverlayDisplaySessionTaskClass[];

PanelModeDataTable gPanelModeDataPointers = {{
    gMenuResourceCacheTaskClass,
    gBoardScreenTaskDescriptor,
    gMenuListTaskClass,
    gMenuResourceCacheTaskClass,
    gOverlayDisplaySessionTaskClass,
}};
