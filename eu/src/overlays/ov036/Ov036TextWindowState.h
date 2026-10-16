#ifndef KH_RECODED_OV036_TEXT_WINDOW_STATE_H
#define KH_RECODED_OV036_TEXT_WINDOW_STATE_H

#include "nitro/types.h"

typedef struct Ov036TextWindowSize {
    s32 width;
    s32 height;
} Ov036TextWindowSize;

typedef struct Ov036TextWindowFont {
    void *resource;
    u16 (*splitChar)(const void **text);
} Ov036TextWindowFont;

typedef struct Ov036TextWindowState {
    u8 pad_0000[0x644c];
    Ov036TextWindowFont mainFont;
    u8 pad_6454[0x68a0 - 0x6454];
    s32 choiceResult;
    u8 pad_68a4[4];
    Ov036TextWindowFont subFont;
} Ov036TextWindowState;

typedef char Ov036TextWindowFontSize[sizeof(Ov036TextWindowFont) == 8 ? 1 : -1];
typedef char Ov036TextWindowMainFontOffset[(u32)&((Ov036TextWindowState *)0)->mainFont == 0x644c ? 1 : -1];
typedef char Ov036TextWindowSubFontOffset[(u32)&((Ov036TextWindowState *)0)->subFont == 0x68a8 ? 1 : -1];
typedef char Ov036TextWindowChoiceOffset[(u32)&((Ov036TextWindowState *)0)->choiceResult == 0x68a0 ? 1 : -1];

extern Ov036TextWindowState *gTextWindowResourceTable;
void MeasureSegmentedTextWindowTiles(Ov036TextWindowSize *outTiles, int screen, const u16 *text, int padX, int padY);

#endif
