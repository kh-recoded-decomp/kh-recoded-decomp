#ifndef STAGE_CAPTION_H
#define STAGE_CAPTION_H

#include "nitro/types.h"
#include "nnsys/g2d.h"

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
    u32 messageId; /* for a requested line: the HUD entry id */
    s16 charStart;
    s16 charBase;
    u16 width;
    u16 rows;
    int offset;
    int fixedStart;
} StageTextLine;

/* A HUD entry: the message it shows and how many rows it takes. */
typedef struct StageHudEntry {
    u32 id;
    u32 messageId;
    int rows;
} StageHudEntry;

/* Two messages that, shown one after the other, are replaced by a single combined one. */
typedef struct StageCaptionCombo {
    u32 first;
    u32 second;
    u32 combined;
} StageCaptionCombo;

/* Three caption lines whose items show these menu icons are shown as the combined entry. */
typedef struct StageCaptionTriple {
    u32 first;
    u32 second;
    u32 third;
    u32 combined;
} StageCaptionTriple;

/* Where each line style's frame tiles start in the caption characters, in bytes. */
typedef struct StageCaptionFrameTiles {
    u32 offsets[5];
} StageCaptionFrameTiles;

/* A queued line as handed out: its message and how many rows it takes. */
typedef struct StageCaptionLineRef {
    u32 messageId;
    int rows;
} StageCaptionLineRef;

/* The surface a text layer draws into: its character canvas and the characters themselves. */
typedef struct StageTextSurface {
    u8 reserved00[0x24];
    u8 *chars;
} StageTextSurface;

/* A caption line on a text layer, with its own character data and message file. */
typedef struct StageCaption {
    u8 reserved000[0x20]; /* the text layer */
    StageTextSurface *surface;
    u8 reserved024[8];
    u16 tileBase;
    u8 reserved02e[0x44 - 0x2e];
    int charOffset; /* where the next line's characters go, in pixels */
    int lineCount; /* lines laid out so far */
    int unk4c;
    int unk50;
    int queuedCount;
    StageTextLine lines[3];
    StageTextLine queued[3];
    StageTextLine notice;
    StageTextLine line;
    int state;
    int previousState;
    void *charData;
    NNSG2dCharacterData *unpackedChars;
    void *messages;
    u8 reserved10c[8];
    BOOL hidden;
} StageCaption;

typedef char StageCaptionLineOffset[(u32)&((StageCaption *)0)->line == 0xe4 ? 1 : -1];
typedef char StageCaptionStateOffset[(u32)&((StageCaption *)0)->state == 0xf8 ? 1 : -1];
typedef char StageCaptionHiddenOffset[(u32)&((StageCaption *)0)->hidden == 0x114 ? 1 : -1];

#endif
