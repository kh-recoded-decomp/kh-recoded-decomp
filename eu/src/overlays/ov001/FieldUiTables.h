#ifndef RECODED_FIELD_UI_TABLES_H
#define RECODED_FIELD_UI_TABLES_H

#include "nitro/types.h"
#include "nitro/fx.h"

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

typedef struct FieldWorldNameOffsets {
    int offsets[11];
} FieldWorldNameOffsets;

typedef struct FieldBalloonTailTiles {
    u16 tiles[4][3][2];
} FieldBalloonTailTiles;

typedef struct FieldScreenPosition {
    fx32 x;
    fx32 y;
} FieldScreenPosition;

typedef struct FieldCounterPalette {
    u16 colors[7];
    u16 alignmentPadding;
} FieldCounterPalette;

typedef struct FieldDifficultyValues {
    int values[4];
} FieldDifficultyValues;

typedef struct FieldNodeOrder {
    int indices[4];
} FieldNodeOrder;

typedef struct FieldHudNodePositions {
    FieldScreenPosition positions[4];
} FieldHudNodePositions;

typedef struct FieldFallingPieceSizes {
    u16 values[4];
} FieldFallingPieceSizes;

extern const FieldDifficultyValues gArrowPromptDifficultySteps;
extern const FieldDifficultyValues gArrowPromptTimeLimits;
extern const FieldDifficultyValues gMinigameStartingLevels;
extern const FieldDifficultyValues gMinigameTimeMultipliers;
extern const FieldFallingPieceSizes gFallingPieceSizes;
extern const FieldScreenPosition gFieldSpriteDefaultPosition;
extern const FieldNodeOrder gFieldSpriteSlotOrder;
extern const FieldNodeOrder gHudNodeOrder;
extern const FieldHudNodePositions gHudNodePositions;
extern const VecFx32 gCrossedGuideTranslation;
extern const VecFx32 gCrossedGuideScale;
extern const MtxFx33 gCrossedGuideIdentityRotation;

extern const FieldWorldNameOffsets gWorldLocationNameOffsets;
extern const FieldWorldNameOffsets gWorldChoiceNameOffsets;
extern const FieldBalloonTailTiles gChoiceBalloonTailTiles;
extern const FieldScreenPosition gScoreTallyPosition;
extern const MtxFx33 gTextureQuadIdentityRotation;
extern const FieldCounterPalette gCounterFadePalette;
extern const int gCounterSwapMovingRecords[4];
extern const int gCounterSwapSettledRecords[4];

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

typedef struct FieldCourseRewardEntry {
    s16 itemId;
    u16 reserved02;
    u8 category;
    u8 rarity;
    u16 reserved06;
} FieldCourseRewardEntry;

extern const u32 gChoiceSceneAnimationRecords[3];
extern const s32 gChoiceDetailTextColors[3];
extern const u32 gMenuGaugePointLevelFileIds[4];
extern const s32 gPanelPrimaryModeRecords[5];
extern const FieldCourseRewardEntry gCourseFallbackReward;
extern const u16 gCourseRecordBitOffsets[9][4];
extern const u32 gCourseRankThresholds[9][3];
extern const FieldCourseRewardEntry gCourseRewardEntries[9][6];

#endif
