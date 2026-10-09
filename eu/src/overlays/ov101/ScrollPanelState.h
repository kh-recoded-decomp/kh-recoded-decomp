#ifndef OV101_SCROLL_PANEL_STATE_H
#define OV101_SCROLL_PANEL_STATE_H

#include "nitro/types.h"

typedef struct {
    s32 listId;
    s32 pageRows;
    s32 totalRows;
    s32 cursorEntry;
    s32 upArrowEntry;
    s32 downArrowEntry;
    s32 barEntry;
    s32 unk_1C;
    s32 unk_20;
    s32 unk_24;
    s32 unk_28;
    s32 scroll;
    s32 cursor;
    s32 trackLength;
    s32 barMarginTop;
    s32 barMarginBottom;
    s32 barStep;
    s32 thumbLength;
    s32 thumbSteps;
} ScrollPanel;

typedef struct {
    u8 pad_0000[0xCD6C];
    ScrollPanel panels[2];
} Ov101ScrollPanelState;

#endif
