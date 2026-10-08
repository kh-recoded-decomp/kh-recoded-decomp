#include "nitro/types.h"

typedef struct {
    u8 pad_00[0xe];
    u16 flags;
    u8 pad_10[4];
    u8 entryIndex;
    u8 holdStage;
    u8 holdReady;
} FieldButton;

typedef struct PartyEntry {
    u8 pad_000[0x1dc];
    int state;
    u8 pad_1e0[0x4c];
    int (*getState)(struct PartyEntry *entry);
} PartyEntry;

typedef struct {
    u32 unk_00 : 9;
    u32 altControls : 1;
    u32 unk_10 : 22;
} ControlConfig;

typedef struct {
    u8 pad_0000[0x2878];
    ControlConfig controls;
} SaveData;

extern SaveData *g_saveData_0205fe0c;
extern u8 data_ov021_020b5600;
extern PartyEntry *GetBoundedEntryField_0206db5c(int index);
extern BOOL HasFlagsAt0xe_020a752c(FieldButton *button, u16 mask);

void ToggleFieldButtonFlags_020a6fd8(FieldButton *button) {
    PartyEntry *entry = GetBoundedEntryField_0206db5c(button->entryIndex);
    u16 flags = button->flags;
    int state;
    if (entry->getState != NULL) {
        state = entry->getState(entry);
    } else {
        state = entry->state;
    }
    if (state != 11) {
        return;
    }
    if (g_saveData_0205fe0c->controls.altControls == 1 && button->entryIndex == data_ov021_020b5600 &&
        HasFlagsAt0xe_020a752c(button, 0x200)) {
        if (button->holdStage > 1) {
            return;
        }
        if (button->holdStage == 1 && button->holdReady == 0) {
            return;
        }
    }
    if (flags & 0x40) {
        button->flags |= 0x80;
        button->flags &= 0xffbf;
    } else if (flags & 0x80) {
        button->flags |= 0x40;
        button->flags &= 0xff7f;
    }
    if (flags & 0x20) {
        button->flags |= 0x10;
        button->flags &= 0xffdf;
    } else if (flags & 0x10) {
        button->flags |= 0x20;
        button->flags &= 0xffef;
    }
}
