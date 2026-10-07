#ifndef KH_RECODED_OV015_PANEL_WORK_H
#define KH_RECODED_OV015_PANEL_WORK_H

#include "nitro/types.h"

typedef struct Ov015PanelWork {
    u8 pad_00[8];
    u32 mode;
    u32 pendingMode;
} Ov015PanelWork;

extern Ov015PanelWork *data_ov015_020812e0;
#define gOv015PanelWork data_ov015_020812e0

#endif
