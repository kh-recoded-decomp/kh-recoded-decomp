#ifndef RECODED_FIELD_GRAPHICS_TABLES_H
#define RECODED_FIELD_GRAPHICS_TABLES_H

#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct FieldGlowColors {
    u8 nearColor[3];
    u8 farColor[3];
} FieldGlowColors;

typedef struct FieldGlowLevelPalette {
    FieldGlowColors entries[4];
    u8 padding;
} FieldGlowLevelPalette;

typedef struct FieldCursorModelIds {
    u32 ids[4];
} FieldCursorModelIds;

/* Packed geometry FIFO: polygon, begin, colour and first vertex, followed
 * by three XZ vertices and end. Coordinates retain the DS Q12 format. */
typedef struct FieldActorQuadPacket {
    u32 commands0;
    u32 polygonAttributes;
    u32 primitive;
    u32 color;
    fx16 firstVertex[3];
    u16 firstVertexPadding;
    u32 commands1;
    fx16 remainingVerticesXZ[3][2];
    u32 commandPadding;
} FieldActorQuadPacket;

typedef struct FieldScriptTargetOperand {
    s16 type;
    s16 reserved02;
    s32 value;
} FieldScriptTargetOperand;

typedef struct FieldSpawnerDelayRange {
    fx32 min;
    fx32 max;
} FieldSpawnerDelayRange;

typedef struct FieldSpawnerDelayTable {
    FieldSpawnerDelayRange ranges[4];
} FieldSpawnerDelayTable;

typedef struct FieldStageDisplayStyle {
    s32 animation;
    s32 alpha;
    s32 offsetIndex;
    fx32 scale;
    s32 blend;
    s32 tint;
} FieldStageDisplayStyle;

typedef struct FieldStageEventKind {
    u32 action;
    u32 attachKey;
    u32 objectId;
    u32 mirrored;
    s32 duration;
} FieldStageEventKind;

typedef struct FieldStageEventKindTable {
    FieldStageEventKind entries[10];
} FieldStageEventKindTable;

extern const u8 gProximityGlowNearColor[3];
extern const FieldGlowLevelPalette gProximityGlowLevelColors;
extern const FieldCursorModelIds gCursorModelIds;
extern const FieldActorQuadPacket gDefaultActorQuadPacket;
extern const s32 gResourceSlotLoadOrder[21];
/* The last element is the original alignment word, not a fourth colour. */
extern const u16 gScreenFadeColors[4];
extern const VecFx32 gScreenFadeCameraUp;
extern const VecFx32 gScreenFadeBaseScale;
extern const VecFx32 gScreenFadeBaseTranslation;
extern const VecFx32 gScreenFadeCameraPosition;
extern const FieldScriptTargetOperand gFaceTargetDefaultOperand;
extern const fx32 gNodeRotationCorrectionQuaternion[4];
/* Only the first five entries are used; the last three preserve alignment. */
extern const u8 gSessionRankValues[8];
extern const u32 gLaunchedActorKindIds[5];
extern const BOOL gGroupCommandResetStates[12];
extern const FieldSpawnerDelayTable gSpawnerDifficultyDelayRanges;
extern const FieldStageDisplayStyle gStageEventDisplayStyles[5];
extern const FieldStageEventKindTable gStageEventKinds;

#endif
