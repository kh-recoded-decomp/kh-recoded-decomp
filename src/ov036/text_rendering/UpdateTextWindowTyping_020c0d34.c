#include "nitro/types.h"

typedef struct WindowInput {
    u8 pad_00[0xc];
    BOOL skipRequested;
} WindowInput;

typedef struct TextWindowEntry {
    s32 state;
    u8 pad_004[0x108];
    WindowInput *input;
} TextWindowEntry;

extern u16 data_02060500;
extern BOOL func_ov036_020bf0f0(TextWindowEntry *window);
extern BOOL func_ov036_020beeec(TextWindowEntry *window);
extern void func_ov036_020c27dc(TextWindowEntry *window, int state);

void UpdateTextWindowTyping_020c0d34(TextWindowEntry *window)
{
    WindowInput *input;
    BOOL done;

    switch (window->state) {
    case 4:
        input = window->input;
        done = func_ov036_020bf0f0(window);
        if ((data_02060500 & 1) || (data_02060500 & 0x200) || (data_02060500 & 0x100) || (data_02060500 & 0x80)) {
            input->skipRequested = TRUE;
        }
        if (done) {
            input->skipRequested = FALSE;
            func_ov036_020c27dc(window, 7);
        }
        break;
    case 0:
        input = window->input;
        done = func_ov036_020beeec(window);
        if ((data_02060500 & 1) || (data_02060500 & 0x200) || (data_02060500 & 0x100) || (data_02060500 & 0x80)) {
            input->skipRequested = TRUE;
        }
        if (done) {
            input->skipRequested = FALSE;
            func_ov036_020c27dc(window, 7);
        }
        break;
    default:
        func_ov036_020c27dc(window, 7);
        break;
    }
}
