#include "src/overlays/ov001/FieldSpriteTables.h"

extern void DrawFieldScreenPiece(void *piece);
extern void ClearFieldScreenPiece(void *piece);

const FieldScreenLayerConfig gMenuScreenLayerConfig = {
    297, 15, 11, DrawFieldScreenPiece, ClearFieldScreenPiece
};
