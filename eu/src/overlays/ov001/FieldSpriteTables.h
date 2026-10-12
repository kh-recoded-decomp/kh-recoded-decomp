#ifndef RECODED_FIELD_SPRITE_TABLES_H
#define RECODED_FIELD_SPRITE_TABLES_H

#include "nitro/types.h"

typedef struct FieldSpriteFile {
    u32 fileIndex;
    u32 parameter;
    s32 instanceCount;
} FieldSpriteFile;

typedef struct FieldSpriteFiles2 {
    FieldSpriteFile entries[2];
} FieldSpriteFiles2;

typedef struct FieldSpriteFiles4 {
    FieldSpriteFile entries[4];
} FieldSpriteFiles4;

typedef struct FieldSpriteFiles5 {
    FieldSpriteFile entries[5];
} FieldSpriteFiles5;

typedef struct FieldSpriteName {
    const char *name;
    u32 parameter;
    s32 instanceCount;
} FieldSpriteName;

typedef struct FieldEffectGroup {
    u32 fileIndex;
    BOOL fixedSlots;
    s32 slotCount;
} FieldEffectGroup;

typedef struct FieldEffectGroups {
    FieldEffectGroup groups[2];
} FieldEffectGroups;

typedef void (*FieldScreenPieceCallback)(void *piece);

typedef struct FieldScreenLayerConfig {
    s32 pieceCapacity;
    s32 capacity30;
    s32 capacity10;
    FieldScreenPieceCallback draw;
    FieldScreenPieceCallback clear;
} FieldScreenLayerConfig;

extern const s16 gLevelBonusWeights[3][3];
extern const FieldSpriteName gLocalizedFieldSprite;
extern const FieldSpriteFile gMode6Sprite;
extern const FieldSpriteFiles2 gMode4Sprites;
extern const FieldEffectGroups gFieldEffectGroups;
extern const FieldSpriteFiles4 gNormalModeSprites;
extern const FieldSpriteFiles5 gCommonModeSprites;
extern const FieldScreenLayerConfig gMenuScreenLayerConfig;

#endif
