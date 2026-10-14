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

extern BoardHelpGlobals data_ov024_020b7540;
extern int GetLanguageIndex(void);
extern const u16 *func_ov027_020ba2c8(const PackedTextView *view, int index);
extern u16 *func_ov027_020ba300(const PackedTextView *view, unsigned index,
                              u16 *buffer, unsigned capacity, ...);
extern void CallVirtualHandlerSlot1(void *layer, u32 value);
extern void *GetFieldFont2(void);
extern void func_02001620(void *layer, u32 x, u32 y, u32 color, u32 flags,
                         const u16 *text, void *font, int maxWidth);
extern void FlushBufferAndRunCallback(void *layer);

void UpdateBoardHelpText(void)
{
    u16 helpText[0x40];
    u16 valueText[0x40];
    const u16 *text;
    int value;

    if (data_ov024_020b7540.cursor->selectedType >= 0 &&
        data_ov024_020b7540.cursor->selectedSlot >= 0) {
        if (data_ov024_020b7540.state->helpMode == 0) {
            return;
        }
        data_ov024_020b7540.state->helpMode = 0;
        if (data_ov024_020b7540.cursor->selectedType == 0x16 &&
            data_ov024_020b7540.cursor->value == 1) {
            text = func_ov027_020ba2c8(&data_ov024_020b7540.state->messages, 0x3e);
        } else if (data_ov024_020b7540.cursor->selectedType == 0x18 &&
                   data_ov024_020b7540.cursor->value == 1) {
            text = func_ov027_020ba2c8(&data_ov024_020b7540.state->messages, 0x3f);
        } else if (data_ov024_020b7540.cursor->selectedType == 0x19 &&
                   data_ov024_020b7540.cursor->value == 1) {
            text = func_ov027_020ba2c8(&data_ov024_020b7540.state->messages, 0x40);
        } else if (data_ov024_020b7540.cursor->selectedType == 0x1d &&
                   data_ov024_020b7540.cursor->value == 1) {
            text = func_ov027_020ba2c8(&data_ov024_020b7540.state->messages, 0x41);
        } else if (data_ov024_020b7540.cursor->selectedType == 0x1e &&
                   data_ov024_020b7540.cursor->value == 1) {
            text = func_ov027_020ba2c8(&data_ov024_020b7540.state->messages, 0x42);
        } else {
            value = data_ov024_020b7540.cursor->value;
            if (value != 0) {
                /* Types 3..7 use a zero-based value in nonzero language indexes. */
                if ((u8)(s8)(data_ov024_020b7540.cursor->selectedType - 3) <= 4 &&
                    GetLanguageIndex() != 0) {
                    value--;
                }
                text = func_ov027_020ba300(&data_ov024_020b7540.state->messages,
                       data_ov024_020b7540.cursor->selectedType + 3,
                       valueText, 0x40, value);
            } else {
                text = func_ov027_020ba2c8(&data_ov024_020b7540.state->messages,
                       data_ov024_020b7540.cursor->selectedType + 3);
            }
        }
        text = func_ov027_020ba300(&data_ov024_020b7540.state->messages,
                                 0x2a, helpText, 0x40, text);
    } else if (!data_ov024_020b7540.cursor->finished) {
        if (data_ov024_020b7540.state->helpMode == 1) {
            return;
        }
        data_ov024_020b7540.state->helpMode = 1;
        text = func_ov027_020ba2c8(&data_ov024_020b7540.state->messages, 0x2b);
    } else if (data_ov024_020b7540.cursor->progress == data_ov024_020b7540.cursor->goal) {
        if (data_ov024_020b7540.state->helpMode == 2) {
            return;
        }
        data_ov024_020b7540.state->helpMode = 2;
        text = func_ov027_020ba2c8(&data_ov024_020b7540.state->messages, 0x30);
    } else {
        if (data_ov024_020b7540.state->helpMode == 3) {
            return;
        }
        data_ov024_020b7540.state->helpMode = 3;
        text = func_ov027_020ba2c8(&data_ov024_020b7540.state->messages, 0x2f);
    }
    if (text != NULL) {
        CallVirtualHandlerSlot1(data_ov024_020b7540.state->textLayer, 0);
        if (data_ov024_020b7540.state->useCustomFont) {
            func_02001620(data_ov024_020b7540.state->textLayer, 0, 4, 2, 0,
                         text, data_ov024_020b7540.state->smallFont, 0xe0);
        } else {
            func_02001620(data_ov024_020b7540.state->textLayer, 0, 4, 2, 0,
                         text, GetFieldFont2(), 0xe0);
        }
        FlushBufferAndRunCallback(data_ov024_020b7540.state->textLayer);
    }
}
