#ifndef EU_RUNTIME_CONSTANT_TABLES_H
#define EU_RUNTIME_CONSTANT_TABLES_H

#include "nitro/fx_types.h"

typedef struct RuntimeQuaternion {
    fx32 w;
    fx32 x;
    fx32 y;
    fx32 z;
} RuntimeQuaternion;

typedef struct SelectionBitOffsets {
    u32 offsets[3];
} SelectionBitOffsets;

typedef struct KindModeScaleTable {
    fx32 rates[2][4];
} KindModeScaleTable;

typedef struct FlagSelectionScaleTable {
    fx32 rates[6];
} FlagSelectionScaleTable;

typedef struct SlideMovementKeepFlags {
    BOOL keepFirst;
    BOOL keepSecond;
} SlideMovementKeepFlags;

extern const RuntimeQuaternion gMatrixCorrectionQuaternion;
extern const RuntimeQuaternion gIdentityMotionQuaternion;
extern const u8 gCompressedRotationElementMap[9][4];
extern const VecFx32 gCameraAnimationForwardAxis;
extern const u8 gQuaternionNextAxis[4];
extern const SelectionBitOffsets gSelectionLoadBitOffsets;
extern const SelectionBitOffsets gSelectionStoreBitOffsets;
extern const KindModeScaleTable gKindModeScaleFactors;
extern const u32 gMaterialColorOverrideMasks[8];
extern const u8 gBgmSequenceVarPolicies[44];
extern const FlagSelectionScaleTable gFlagSelectionScaleFactors;
extern const SlideMovementKeepFlags gSlideMovementKeepBoth;

#endif
