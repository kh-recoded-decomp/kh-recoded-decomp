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

extern const RuntimeQuaternion gMatrixCorrectionQuaternion;
extern const u8 gQuaternionNextAxis[4];
extern const SelectionBitOffsets gSelectionLoadBitOffsets;
extern const SelectionBitOffsets gSelectionStoreBitOffsets;
extern const KindModeScaleTable gKindModeScaleFactors;

#endif
