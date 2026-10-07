#include "nitro/types.h"

typedef struct DialogRect {
    s32 left;
    s32 top;
    s32 right;
    s32 bottom;
} DialogRect;

const DialogRect sDefaultDialogRect = {
    0x00000000, 0x00093008, 0x00000010, 0x00034000,
};
