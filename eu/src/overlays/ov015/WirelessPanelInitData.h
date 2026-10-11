#ifndef KH_RECODED_WIRELESS_PANEL_INIT_DATA_H
#define KH_RECODED_WIRELESS_PANEL_INIT_DATA_H

#include "nitro/types.h"

typedef struct ContextFlagMasks {
    u32 words[3];
} ContextFlagMasks;

typedef struct PanelWidgetIds {
    s32 ids[3];
} PanelWidgetIds;

typedef struct WirelessPanelBgConfig {
    u32 counts[5];
} WirelessPanelBgConfig;

typedef struct WirelessPanelObjConfig {
    u32 cellFileId;
    u32 parameters[4];
    u32 animFileId;
} WirelessPanelObjConfig;

extern const WirelessPanelBgConfig gWirelessMainBgConfig;
extern const WirelessPanelBgConfig gWirelessSubBgConfig;
extern const WirelessPanelObjConfig gWirelessMainObjConfig;
extern const WirelessPanelObjConfig gWirelessSubObjConfig;

#endif
