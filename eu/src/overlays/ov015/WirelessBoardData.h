#ifndef KH_RECODED_WIRELESS_BOARD_DATA_H
#define KH_RECODED_WIRELESS_BOARD_DATA_H

#include "nitro/types.h"

typedef struct WirelessBoardSlotPosition {
    s16 x;
    s16 y;
} WirelessBoardSlotPosition;

extern const WirelessBoardSlotPosition *gWirelessModeDataTables[10];
extern const u32 gWirelessRandomChoiceLimits[11];
extern const WirelessBoardSlotPosition gWirelessBoardSlotPositions3[3];
extern const WirelessBoardSlotPosition gWirelessBoardSlotPositions4[4];
extern const WirelessBoardSlotPosition gWirelessBoardSlotPositions5[5];
extern const WirelessBoardSlotPosition gWirelessBoardSlotPositions6[6];
extern const WirelessBoardSlotPosition gWirelessBoardSlotPositions7[7];
extern const WirelessBoardSlotPosition gWirelessBoardSlotPositions8[8];
extern const WirelessBoardSlotPosition gWirelessBoardSlotPositions9[9];

typedef struct WirelessSlotStyle {
    s8 slotX;
    s8 priority;
    u8 parameters02[2];
} WirelessSlotStyle;

typedef struct WirelessThemeEntry {
    s8 bgIndex;
    s8 charIndex;
    u8 parameters02[23];
} WirelessThemeEntry;

typedef struct WirelessThemeData {
    u16 parameters00;
    WirelessThemeEntry themes[10];
} WirelessThemeData;

typedef struct WirelessBoardObjConfig {
    u32 cellFileId;
    u32 parameters04[3];
    int count;
    u32 animFileId;
} WirelessBoardObjConfig;

extern const WirelessThemeData gWirelessThemeData;
extern const WirelessThemeEntry gWirelessThemes[10];
extern const WirelessSlotStyle gWirelessSlotStyles[79];
extern const WirelessBoardObjConfig gWirelessBoardObjConfig;

#endif
