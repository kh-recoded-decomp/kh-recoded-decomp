#ifndef RECODED_FIELD_UI_TABLES_H
#define RECODED_FIELD_UI_TABLES_H

#include "nitro/types.h"

typedef struct FieldTextFrame {
    u16 x;
    u16 y;
    u16 width;
    u16 height;
    u16 charBase;
    u16 palette;
    u16 hSpace;
    u16 vSpace;
} FieldTextFrame;

typedef struct FieldSlotOrder {
    int slots[3];
} FieldSlotOrder;

typedef struct FieldWidgetLayerList {
    int ids[3];
} FieldWidgetLayerList;

typedef struct FieldMenuButtonRecordTable {
    u32 recordIds[2][2][3];
} FieldMenuButtonRecordTable;

typedef struct FieldWindowScrollArrowTiles {
    u16 tiles[4][3][2];
} FieldWindowScrollArrowTiles;

typedef struct FieldMessageWindowGraphicsSlots {
    int slots[11];
} FieldMessageWindowGraphicsSlots;

extern const FieldTextFrame gMessageLineTextFrame;
extern const FieldTextFrame gRecordNameTextFrame;
extern const FieldTextFrame gSceneTextFrame4D8;
extern const FieldTextFrame gSceneTextFrame51C;
extern const FieldTextFrame gChoiceTextFrame;
extern const FieldTextFrame gSlotLabelTextFrame;
extern const FieldTextFrame gFieldHudTextFrame;
extern const FieldTextFrame gFieldCommandTextFrame;
extern const FieldTextFrame gCategoryLabelTextFrame;
extern const FieldMenuButtonRecordTable gFieldMenuButtonRecords;
extern const FieldWindowScrollArrowTiles gWindowScrollArrowTiles;
extern const FieldMessageWindowGraphicsSlots gMessageWindowGraphicsSlots;
extern const FieldSlotOrder gFieldSlotOrder;
extern const FieldWidgetLayerList gVramRestoreWidgetLayers;
extern const FieldWidgetLayerList gVramBackupWidgetLayers;

/* Six 4-bit colour indices per gauge row. The two transition rows follow the fill. */
extern const u8 gGaugeFilledRow[6];
extern const u8 gGaugeEmptyRow[6];
extern const u8 gGaugeTransitionRow1[6];
extern const u8 gGaugeTransitionRow2[6];

#endif
