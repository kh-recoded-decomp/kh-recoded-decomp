#pragma optimization_level 3
#include "nitro/types.h"

typedef struct PackedTextView {
    u32 key;
    u32 count;
    const u8 *records;
} PackedTextView;

typedef struct BoardHelpState {
    u8 reserved0000[0x6500];
    PackedTextView messages;
    u8 normalFont[0xc];
    u8 smallFont[0xc];
    u8 textLayer[0x66e0 - 0x6524];
    BOOL useCustomFont;
    u8 reserved66e4[0x66fe - 0x66e4];
    s8 helpMode;
} BoardHelpState;

typedef struct BoardHelpCursor {
    u8 reserved00[0xc];
    u16 value;
    u8 reserved0e[0x23 - 0xe];
    s8 selectedSlot;
    u8 progress;
    u8 goal;
    s8 selectedType;
    u8 reserved27[0x88 - 0x27];
    BOOL finished;
} BoardHelpCursor;

typedef struct BoardHelpGlobals {
    BoardHelpState *state;
    u32 reserved04;
    BoardHelpCursor *cursor;
} BoardHelpGlobals;

extern BoardHelpGlobals gBoardScreenGlobals;
extern int GetLanguageIndex(void);
extern const u16 *GetPackedFileEntry(const PackedTextView *view, int index);
extern u16 *FormatPackedWideText(const PackedTextView *view, unsigned index,
                              u16 *buffer, unsigned capacity, ...);
extern void CallVirtualHandlerSlot1(void *layer, u32 value);
extern void *GetFieldFont2(void);
extern void DrawTextAnchoredWithFontFallback(void *layer, u32 x, u32 y, u32 color, u32 flags,
                         const u16 *text, void *font, int maxWidth);
extern void FlushBufferAndRunCallback(void *layer);

void UpdateBoardHelpText(void)
{
    u16 helpText[0x40];
    u16 valueText[0x40];
    const u16 *text;
    int value;

    if (gBoardScreenGlobals.cursor->selectedType >= 0 &&
        gBoardScreenGlobals.cursor->selectedSlot >= 0) {
        if (gBoardScreenGlobals.state->helpMode == 0) {
            return;
        }
        gBoardScreenGlobals.state->helpMode = 0;
        if (gBoardScreenGlobals.cursor->selectedType == 0x16 &&
            gBoardScreenGlobals.cursor->value == 1) {
            text = GetPackedFileEntry(&gBoardScreenGlobals.state->messages, 0x3e);
        } else if (gBoardScreenGlobals.cursor->selectedType == 0x18 &&
                   gBoardScreenGlobals.cursor->value == 1) {
            text = GetPackedFileEntry(&gBoardScreenGlobals.state->messages, 0x3f);
        } else if (gBoardScreenGlobals.cursor->selectedType == 0x19 &&
                   gBoardScreenGlobals.cursor->value == 1) {
            text = GetPackedFileEntry(&gBoardScreenGlobals.state->messages, 0x40);
        } else if (gBoardScreenGlobals.cursor->selectedType == 0x1d &&
                   gBoardScreenGlobals.cursor->value == 1) {
            text = GetPackedFileEntry(&gBoardScreenGlobals.state->messages, 0x41);
        } else if (gBoardScreenGlobals.cursor->selectedType == 0x1e &&
                   gBoardScreenGlobals.cursor->value == 1) {
            text = GetPackedFileEntry(&gBoardScreenGlobals.state->messages, 0x42);
        } else {
            value = gBoardScreenGlobals.cursor->value;
            if (value != 0) {
                /* Types 3..7 use a zero-based value in nonzero language indexes. */
                if ((u8)(s8)(gBoardScreenGlobals.cursor->selectedType - 3) <= 4 &&
                    GetLanguageIndex() != 0) {
                    value--;
                }
                text = FormatPackedWideText(&gBoardScreenGlobals.state->messages,
                       gBoardScreenGlobals.cursor->selectedType + 3,
                       valueText, 0x40, value);
            } else {
                text = GetPackedFileEntry(&gBoardScreenGlobals.state->messages,
                       gBoardScreenGlobals.cursor->selectedType + 3);
            }
        }
        text = FormatPackedWideText(&gBoardScreenGlobals.state->messages,
                                 0x2a, helpText, 0x40, text);
    } else if (!gBoardScreenGlobals.cursor->finished) {
        if (gBoardScreenGlobals.state->helpMode == 1) {
            return;
        }
        gBoardScreenGlobals.state->helpMode = 1;
        text = GetPackedFileEntry(&gBoardScreenGlobals.state->messages, 0x2b);
    } else if (gBoardScreenGlobals.cursor->progress == gBoardScreenGlobals.cursor->goal) {
        if (gBoardScreenGlobals.state->helpMode == 2) {
            return;
        }
        gBoardScreenGlobals.state->helpMode = 2;
        text = GetPackedFileEntry(&gBoardScreenGlobals.state->messages, 0x30);
    } else {
        if (gBoardScreenGlobals.state->helpMode == 3) {
            return;
        }
        gBoardScreenGlobals.state->helpMode = 3;
        text = GetPackedFileEntry(&gBoardScreenGlobals.state->messages, 0x2f);
    }
    if (text != NULL) {
        CallVirtualHandlerSlot1(gBoardScreenGlobals.state->textLayer, 0);
        if (gBoardScreenGlobals.state->useCustomFont) {
            DrawTextAnchoredWithFontFallback(gBoardScreenGlobals.state->textLayer, 0, 4, 2, 0,
                         text, gBoardScreenGlobals.state->smallFont, 0xe0);
        } else {
            DrawTextAnchoredWithFontFallback(gBoardScreenGlobals.state->textLayer, 0, 4, 2, 0,
                         text, GetFieldFont2(), 0xe0);
        }
        FlushBufferAndRunCallback(gBoardScreenGlobals.state->textLayer);
    }
}
