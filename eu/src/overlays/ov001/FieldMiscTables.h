#ifndef FIELD_MISC_TABLES_H
#define FIELD_MISC_TABLES_H

#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct FieldScreenPoint {
    fx32 x;
    fx32 y;
} FieldScreenPoint;

typedef struct ScreenSpriteVariants {
    s8 entries[10];
    u8 padding[2];
} ScreenSpriteVariants;

typedef struct ButtonPanelOffsets {
    s32 values[4];
} ButtonPanelOffsets;

typedef struct FieldCornerOffsets {
    FieldScreenPoint corners[4];
} FieldCornerOffsets;

typedef struct ManagerSpriteFileIds {
    u32 ids[7];
} ManagerSpriteFileIds;

typedef struct SlotLabelMessageIds {
    int ids[2];
} SlotLabelMessageIds;

extern const s16 gRandomEnemyDropIds[13];
extern const FieldScreenPoint gCenteredScreenSpritePosition;
extern const FieldScreenPoint gCounterHudDigitPosition;
extern const ScreenSpriteVariants gCenteredScreenSpriteVariants;
extern const VecFx32 gIrisFrameBaseScale;
extern const ButtonPanelOffsets gButtonPanelOffsets;
extern const FieldCornerOffsets gCornerItemOffsets;
extern const ManagerSpriteFileIds gManagerSpriteFileIds;
extern const SlotLabelMessageIds gSlotLabelMessageIds;

#endif
