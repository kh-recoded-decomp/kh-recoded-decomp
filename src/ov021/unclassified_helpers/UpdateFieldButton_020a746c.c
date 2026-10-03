#include "nitro/types.h"

typedef struct {
    u8 pad_00[4];
    u16 entryValue;
    u8 pad_06[0xe];
    u8 entryIndex;
} FieldButton;

extern u8 data_ov021_020b5600;
extern void func_ov021_020a6edc(FieldButton *button);
extern BOOL func_ov001_02064490(void);
extern int func_ov001_02063a38(void);
extern BOOL HasFlagsAt0xe_020a752c(FieldButton *button, u32 mask);
extern void func_ov021_020a6fd8(FieldButton *button);
extern void func_ov021_020a6f34(FieldButton *button);
extern void UpdateFieldButtonInput_020a70a8(FieldButton *button);
extern void func_ov021_020a74f0(FieldButton *button);
extern void *GetBoundedEntryField_0206db5c(int index);
extern u16 func_ov058_020d5f04(void *entry, FieldButton *button);

void UpdateFieldButton_020a746c(FieldButton *button)
{
    BOOL refresh;

    if (button->entryIndex == data_ov021_020b5600) {
        refresh = TRUE;
        func_ov021_020a6edc(button);
        if (func_ov001_02064490()) {
            refresh = FALSE;
        }
        if (func_ov001_02063a38() != 7 && HasFlagsAt0xe_020a752c(button, 0x100) && HasFlagsAt0xe_020a752c(button, 0x200)) {
            refresh = FALSE;
        }
        if (refresh) {
            func_ov021_020a6fd8(button);
            func_ov021_020a6f34(button);
        }
        UpdateFieldButtonInput_020a70a8(button);
        return;
    }
    func_ov021_020a74f0(button);
    if (button->entryIndex != 0) {
        button->entryValue = func_ov058_020d5f04(GetBoundedEntryField_0206db5c(button->entryIndex), button);
        func_ov021_020a6fd8(button);
        func_ov021_020a6f34(button);
    }
}
