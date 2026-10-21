#ifndef STAGE_CAPTION_H
#define STAGE_CAPTION_H

#include "nitro/types.h"

/* Where and how a text layer draws (tiles, character base and palette). */
typedef struct StageTextFrame {
    u16 x;
    u16 y;
    u16 width;
    u16 height;
    u16 charBase;
    u16 palette;
    u16 hSpace;
    u16 vSpace;
} StageTextFrame;

/* A caption line on a text layer, with its own character data and message file. */
typedef struct StageCaption {
    u8 textLayer[0xf8];
    int state;
    int previousState;
    void *charData;
    void *unpackedChars;
    void *messages;
} StageCaption;

#endif
