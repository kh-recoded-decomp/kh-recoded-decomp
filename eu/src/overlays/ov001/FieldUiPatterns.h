#ifndef RECODED_FIELD_UI_PATTERNS_H
#define RECODED_FIELD_UI_PATTERNS_H

#include "nitro/types.h"

typedef struct FieldCellIds {
    u32 words[7];
} FieldCellIds;

typedef struct FieldResumeLayerIds {
    int ids[7];
} FieldResumeLayerIds;

typedef struct FieldEntryModes {
    int values[3];
} FieldEntryModes;

typedef struct FieldSlotMessageIds {
    int messageIds[4];
} FieldSlotMessageIds;

typedef struct FieldSlotRecordIds {
    int ids[8];
} FieldSlotRecordIds;

typedef struct FieldWidgetLayerIds {
    int ids[3];
} FieldWidgetLayerIds;

typedef void (*FieldGaugeRowDraw)(u8 *tiles, int right, int row);

typedef struct FieldGaugeLayout {
    int reserved00;
    int rowWidth;
    int cellCount;
    int topRow;
    const u8 *shadeRamp;
    int rowCount;
    FieldGaugeRowDraw drawRow;
} FieldGaugeLayout;

extern const FieldCellIds gMenuScreenCellIds;
extern const FieldResumeLayerIds gResumeFieldLayerIds;
extern const FieldEntryModes gFieldEntryModes;
extern const FieldSlotMessageIds gFieldSlotMessageIds;
extern const FieldSlotRecordIds gFieldSlotHudRecordIds;
extern const FieldWidgetLayerIds gFieldHudRefreshLayerIds;
extern const FieldWidgetLayerIds gFieldHudRestoreLayerIds;
extern const u8 gWideGaugeShadeRamp[7];
extern const u8 gNarrowGaugeShadeRamp[7];
extern FieldGaugeLayout gFieldGaugeLayouts[2];

/* These are short patterns of 4-bit palette indices, not text strings. */
extern const u8 gFourPixelLabelRows[5][4];
extern const u8 gFourPixelInsetRows[2][4];
extern const u8 gShortLayoutRowsA[5][5];
extern const u8 gShortLayoutRowsB[6][5];
extern const u8 gShortLabelRows[6][7];

void BlitFourPixelLabelPattern(u8 *tiles, int right, s32 patternIndex);
void BlitFourPixelInsetPattern(u8 *tiles, int right, s32 patternIndex);

#endif
