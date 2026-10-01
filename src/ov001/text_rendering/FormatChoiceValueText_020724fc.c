#include "nitro/types.h"

typedef struct FieldManager {
    u8 pad_000[0x490];
    char valueText[0x20];
    u8 pad_4B0[0x684];
    int choiceValues[1];
} FieldManager;

typedef struct FieldManagerHandle {
    u32 unk_00;
    FieldManager *manager;
} FieldManagerHandle;

extern FieldManagerHandle data_ov001_020a04a4;
extern const char data_ov001_0209edc4[];
extern void ClearChoiceHighlight_020701a8(FieldManager *manager);
extern int OS_SNPrintf_0202e080(char *buffer, u32 size, const char *format, ...);

void FormatChoiceValueText_020724fc(int index)
{
    FieldManager *manager = data_ov001_020a04a4.manager;

    ClearChoiceHighlight_020701a8(manager);
    OS_SNPrintf_0202e080(manager->valueText, 0x20, data_ov001_0209edc4, manager->choiceValues[index]);
}
