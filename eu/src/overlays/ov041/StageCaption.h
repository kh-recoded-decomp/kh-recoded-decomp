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

/* One line of text on the caption layer: its characters start at charStart (8 pixels each). */
typedef struct StageTextLine {
    const void *text;
    s16 charStart;
    u16 charBase;
    u16 width;
    u16 rows;
    int offset;
    int fixedStart;
} StageTextLine;

/* A queued line as handed out: its text and how many rows it takes. */
typedef struct StageCaptionLineRef {
    const void *text;
    int rows;
} StageCaptionLineRef;

/* A caption line on a text layer, with its own character data and message file. */
typedef struct StageCaption {
    u8 reserved000[0x2c]; /* the text layer */
    u16 tileBase;
    u8 reserved02e[0x44 - 0x2e];
    int charOffset; /* where the next line's characters go, in pixels */
    int lineCount; /* lines laid out so far */
    u8 reserved04c[4];
    int unk50;
    int queuedCount;
    StageTextLine lines[3];
    StageTextLine queued[3];
    u8 reserved0d0[0x10];
    int unkE0;
    StageTextLine line;
    int state;
    int previousState;
    void *charData;
    void *unpackedChars;
    void *messages;
    u8 reserved10c[8];
    BOOL hidden;
} StageCaption;

typedef char StageCaptionLineOffset[(u32)&((StageCaption *)0)->line == 0xe4 ? 1 : -1];
typedef char StageCaptionStateOffset[(u32)&((StageCaption *)0)->state == 0xf8 ? 1 : -1];
typedef char StageCaptionHiddenOffset[(u32)&((StageCaption *)0)->hidden == 0x114 ? 1 : -1];

#endif
