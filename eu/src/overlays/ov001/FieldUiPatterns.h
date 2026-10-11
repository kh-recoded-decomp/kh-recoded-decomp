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

extern const FieldCellIds gMenuScreenCellIds;
extern const FieldResumeLayerIds gResumeFieldLayerIds;
extern const FieldEntryModes gFieldEntryModes;
extern const FieldSlotMessageIds gFieldSlotMessageIds;

/* These are short patterns of 4-bit palette indices, not text strings. */
extern const u8 gFourPixelLabelRows[5][4];
extern const u8 gFourPixelInsetRows[2][4];
extern const u8 gShortLayoutRowsA[5][5];
extern const u8 gShortLayoutRowsB[6][5];
extern const u8 gShortLabelRows[6][7];

void BlitFourPixelLabelPattern(u8 *tiles, int right, s32 patternIndex);
void BlitFourPixelInsetPattern(u8 *tiles, int right, s32 patternIndex);

#endif
