#include "nitro/types.h"

typedef struct ScrollState {
    s32 top;
    s32 drawnTop;
    s32 visible;
    s32 cursor;
    s32 count;
    s32 confirmOnLast;
} ScrollState;

typedef struct TwoWordValue {
    int first;
    int second;
} TwoWordValue;

typedef struct RecordEntry {
    s32 recordIndex;
    TwoWordValue position;
    u32 flags;
} RecordEntry;

typedef struct ScrollMenu {
    u8 pad_00[0x3c];
    u8 textLayer[0x46];
    u16 lineSpacing;
    u8 pad_84[0x30];
    RecordEntry entries[5];
    u8 pad_104[0x8];
    ScrollState *scroll;
} ScrollMenu;

extern u8 *data_ov036_020c3844;
extern u8 func_020019f4(void *textLayer);
extern u32 func_0204f5ec(void *input);
extern void func_0204f13c(void *recordBase, int recordIndex, TwoWordValue *sourceValue);
extern BOOL PlaySoundEffect_0204d924(int seqArcNo, int index);
extern void RedrawScrolledTextLayer_020bf3d8(ScrollMenu *menu);
extern void SetRecordEntryEnabled_020bf4fc(RecordEntry *entry, int enabled);
extern void SetTimerDuration_020c27dc(ScrollMenu *menu, int duration);
extern int func_ov036_020c27ec(ScrollMenu *menu);

static inline int LinesToOffset(int lines)
{
    return (int)(lines > 0 ? 0.5f + (float)(lines << 12) : (float)(lines << 12) - 0.5f);
}

void HandleScrollMenuInput_020c180c(ScrollMenu *menu)
{
    ScrollState *scroll = menu->scroll;
    int zero = 0;
    int height = func_020019f4(menu->textLayer);
    int spacing = menu->lineSpacing;
    int i;
    int step;
    int rest;

    switch ((int)(func_0204f5ec(data_ov036_020c3844 + 0x6830) & 0xf1)) {
    case 0x40:
        if (scroll->cursor > 0) {
            if (--scroll->cursor < scroll->top) {
                scroll->top--;
            } else {
                menu->entries[1].position.second -= LinesToOffset(height + spacing);
                func_0204f13c(data_ov036_020c3844 + 0x18, menu->entries[1].recordIndex, &menu->entries[1].position);
            }
            PlaySoundEffect_0204d924(0, 0);
        } else {
            if (*(u16 *)(data_ov036_020c3844 + 0x6836) != 0) {
                break;
            }
            scroll->top = scroll->count - scroll->visible;
            scroll->cursor = scroll->count - 1;
            menu->entries[1].position.second += LinesToOffset((scroll->visible - 1) * (height + spacing));
            func_0204f13c(data_ov036_020c3844 + 0x18, menu->entries[1].recordIndex, &menu->entries[1].position);
            PlaySoundEffect_0204d924(0, 0);
        }
        break;
    case 0x80:
        if (scroll->cursor < scroll->count - 1) {
            if (++scroll->cursor >= scroll->top + scroll->visible) {
                scroll->top++;
            } else {
                menu->entries[1].position.second += LinesToOffset(height + spacing);
                func_0204f13c(data_ov036_020c3844 + 0x18, menu->entries[1].recordIndex, &menu->entries[1].position);
            }
            PlaySoundEffect_0204d924(0, 0);
        } else {
            if (*(u16 *)(data_ov036_020c3844 + 0x6838) != 0) {
                break;
            }
            scroll->top = zero;
            scroll->cursor = zero;
            menu->entries[1].position.second -= LinesToOffset((scroll->visible - 1) * (height + spacing));
            func_0204f13c(data_ov036_020c3844 + 0x18, menu->entries[1].recordIndex, &menu->entries[1].position);
            PlaySoundEffect_0204d924(0, 0);
        }
        break;
    case 0x20:
        step = scroll->top;
        rest = scroll->cursor;
        if (step < 0 || rest <= 0) {
            break;
        }
        if (step > scroll->visible) {
            step = scroll->visible;
        }
        scroll->cursor -= step;
        scroll->top -= step;
        if (step < scroll->visible) {
            scroll->cursor -= rest;
            if (scroll->cursor < 0) {
                rest += scroll->cursor;
                scroll->cursor = zero;
            }
            menu->entries[1].position.second -= LinesToOffset(rest * (height + spacing));
            func_0204f13c(data_ov036_020c3844 + 0x18, menu->entries[1].recordIndex, &menu->entries[1].position);
        }
        PlaySoundEffect_0204d924(0, 0);
        break;
    case 0x10:
        step = scroll->count - (scroll->top + scroll->visible);
        rest = scroll->count - 1 - scroll->cursor;
        if (step < 0 || rest <= 0) {
            break;
        }
        if (step > scroll->visible) {
            step = scroll->visible;
        }
        scroll->cursor += step;
        scroll->top += step;
        if (step < scroll->visible) {
            int last;
            scroll->cursor += rest;
            last = scroll->count - 1;
            if (scroll->cursor > last) {
                rest -= scroll->cursor - last;
                scroll->cursor = last;
            }
            menu->entries[1].position.second += LinesToOffset(rest * (height + spacing));
            func_0204f13c(data_ov036_020c3844 + 0x18, menu->entries[1].recordIndex, &menu->entries[1].position);
        }
        PlaySoundEffect_0204d924(0, 0);
        break;
    case 0x1:
        for (i = 0; i < 5; i++) {
            SetRecordEntryEnabled_020bf4fc(&menu->entries[i], zero);
        }
        if (scroll->confirmOnLast != 0 && scroll->cursor == scroll->count - 1) {
            PlaySoundEffect_0204d924(0, 3);
        } else {
            PlaySoundEffect_0204d924(0, 1);
        }
        SetTimerDuration_020c27dc(menu, 9);
        *(s32 *)(data_ov036_020c3844 + 0x68a0) = scroll->cursor;
        break;
    }

    if (scroll->top != scroll->drawnTop) {
        RedrawScrolledTextLayer_020bf3d8(menu);
        scroll->drawnTop = scroll->top;
    }
    if (func_ov036_020c27ec(menu) == 9) {
        return;
    }
    if (scroll->top == 0) {
        SetRecordEntryEnabled_020bf4fc(&menu->entries[2], 0);
    } else {
        SetRecordEntryEnabled_020bf4fc(&menu->entries[2], 1);
    }
    if (scroll->count == scroll->top + scroll->visible) {
        SetRecordEntryEnabled_020bf4fc(&menu->entries[3], 0);
    } else {
        SetRecordEntryEnabled_020bf4fc(&menu->entries[3], 1);
    }
}
