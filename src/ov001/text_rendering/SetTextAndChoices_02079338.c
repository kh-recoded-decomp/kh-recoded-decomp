#include "nitro/types.h"

typedef struct {
    s32 count;
    s32 initial;
    u16 **strings;
    u32 unk_0c;
} ChoiceList;

typedef struct {
    u8 pad_00[0x38];
    u16 *text;
    u16 *cursor;
    u8 pad_40[0x54 - 0x40];
    ChoiceList choices;
} TextPrompt;

extern int func_02022a38(u16 *text);
extern u16 *copy_padded_utf16_string_02022a74(u16 *destination, u16 *source, int unitCount);
extern void *NNSi_FndAllocFromDefaultHeapEx_0202a19c(u32 size, int align);
extern void MI_CpuFill8_01ff8830(void *dst, u8 val, u32 size);

void SetTextAndChoices_02079338(TextPrompt *prompt, u16 *text, ChoiceList *source) {
    ChoiceList *choices = &prompt->choices;
    int length = func_02022a38(text);
    u16 *buffer = NNSi_FndAllocFromDefaultHeapEx_0202a19c((length + 1) * 2, -4);
    int i;

    prompt->text = buffer;
    prompt->cursor = buffer;
    copy_padded_utf16_string_02022a74(buffer, text, length);
    prompt->text[length] = 0;
    i = 0;
    if (source != NULL) {
        choices->count = source->count;
        choices->initial = source->initial;
        choices->strings = NNSi_FndAllocFromDefaultHeapEx_0202a19c(source->count * 4, -4);
        for (; i < choices->count; i++) {
            u16 *choice = source->strings[i];
            length = func_02022a38(choice);
            choices->strings[i] = NNSi_FndAllocFromDefaultHeapEx_0202a19c((length + 1) * 2, -4);
            copy_padded_utf16_string_02022a74(choices->strings[i], choice, length);
            choices->strings[i][length] = 0;
        }
    } else {
        MI_CpuFill8_01ff8830(choices, 0, sizeof(ChoiceList));
    }
}
