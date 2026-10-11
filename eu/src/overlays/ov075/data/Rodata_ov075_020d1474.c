#include "nitro/types.h"

typedef struct MatrixCursorFrame {
    u8 width;
    u8 height;
    s8 offsetX;
    s8 offsetY;
} MatrixCursorFrame;

const MatrixCursorFrame sMatrixCursorFrames[8] = {
    { 0x10, 0x10, 0, 0 },
    { 0x30, 0x30, 0, 0 },
    { 0x20, 0x20, 0, 0 },
    { 0x20, 0x20, 0, 0 },
    { 0x20, 0x20, 0, 0 },
    { 0x30, 0x30, 0, 0 },
    { 0x40, 0x20, 0, 0 },
    { 0x50, 0x50, 0, 0 },
};
