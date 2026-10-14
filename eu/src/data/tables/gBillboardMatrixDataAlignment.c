#include "nitro/types.h"

#pragma define_section billboardMatrixAlignment ".data" RW

/* Retained zero alignment bytes, not additional matrix elements. */
__declspec(billboardMatrixAlignment) u8 gBillboardMatrixDataAlignment[8] = {0};
