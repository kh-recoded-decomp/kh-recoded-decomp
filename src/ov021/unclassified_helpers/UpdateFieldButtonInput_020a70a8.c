#include "nitro/types.h"

typedef struct {
    u8 pad_00[6];
    u8 unk_06;
    u8 pad_07;
    u32 flags;
    u16 pressed;
    u16 held;
    u16 command;
    s16 subCommand;
    u8 pad_14;
    u8 state;
    u8 timer;
} FieldInput;

typedef struct {
    u32 unk_00 : 9;
    u32 altControls : 1;
    u32 unk_10 : 6;
    u32 swapActions : 1;
    u32 unk_17 : 4;
    u32 keepMenuOpen : 1;
} ControlConfig;

typedef struct {
    u8 pad_0000[0x2878];
    ControlConfig controls;
    u8 pad_287c[0x28d7 - 0x287c];
    u8 unk_28d7 : 4;
    u8 shortcutEntry : 4;
} SaveData;

extern SaveData *g_saveData_0205fe0c;

extern s32 func_ov001_02063a38(void);
extern s32 func_ov001_0206c504(void);
extern s32 func_ov001_02072020(u16 pressed);
extern BOOL func_ov001_02072040(void);
extern void func_ov001_020720cc(s32 enable);
extern u32 func_ov001_02077bcc(void);
extern BOOL func_ov001_02077e68(void);
extern BOOL func_ov001_02077ef4(void);
extern void SelectFieldMenuEntryById_02077f3c(int entryId);
extern void func_ov001_02078360(int a, int b);
extern s32 func_ov001_02078494(void);
extern BOOL PlaySoundEffect_0204d924(int seqArcNo, int index);
extern BOOL func_ov021_020a751c(FieldInput *input, u16 mask);
extern BOOL func_ov021_020a752c(FieldInput *input, u16 mask);
extern u16 GetFieldAt0xc_020a7554(FieldInput *input);

void UpdateFieldButtonInput_020a70a8(FieldInput *input)
{
    s32 mode;
    u16 primaryButton;
    u16 rightButton;
    u16 leftButton;
    s32 menuState;
    u16 secondaryButton;
    u16 shortcutButton;
    u16 swap;
    BOOL played;
    s16 subCommand;

    mode = func_ov001_02063a38();
    if (!func_ov021_020a752c(input, 0x100) && func_ov001_0206c504() > 0x9000) {
        if (func_ov021_020a752c(input, 0x200) && !func_ov001_02072040()) {
            menuState = func_ov001_02078494();
            func_ov001_020720cc(1);
            if (input->state == 0) {
                input->state = 1;
                input->timer = 8;
            } else if (input->timer != 0) {
                input->timer--;
            }
            if (!g_saveData_0205fe0c->controls.altControls) {
                primaryButton = 2;
                secondaryButton = 0x400;
                shortcutButton = 1;
                rightButton = 0x800;
                leftButton = 0x800;
            } else {
                primaryButton = 0x80;
                rightButton = 0x20;
                secondaryButton = 0x40;
                shortcutButton = 0x10;
                leftButton = 0x10;
            }
            if (g_saveData_0205fe0c->controls.swapActions) {
                swap = primaryButton;
                primaryButton = secondaryButton;
                secondaryButton = swap;
            }
            if (g_saveData_0205fe0c->shortcutEntry == 0xf) {
                shortcutButton = 0;
            }
            if (mode == 4 || mode == 7) {
                shortcutButton = 0;
            }
            if (func_ov021_020a751c(input, primaryButton)) {
                input->pressed &= ~primaryButton;
                input->held &= ~primaryButton;
                if (func_ov001_02077ef4()) {
                    PlaySoundEffect_0204d924(0, 0);
                }
                input->state = 2;
            } else if (func_ov021_020a751c(input, secondaryButton)) {
                input->pressed &= ~secondaryButton;
                input->held &= ~secondaryButton;
                if (func_ov001_02077e68()) {
                    PlaySoundEffect_0204d924(0, 0);
                }
                input->state = 2;
            }
            if (mode == 6) {
                played = FALSE;
                if (func_ov001_02077bcc() == 6 || func_ov001_02077bcc() == 9) {
                    leftButton = 0;
                    rightButton = 0;
                }
                if (func_ov021_020a751c(input, leftButton) && menuState == 0) {
                    input->pressed &= ~leftButton;
                    input->held &= ~leftButton;
                    func_ov001_02078360(1, 1);
                    if (func_ov001_02078494() == 1) {
                        PlaySoundEffect_0204d924(0x1a0, 0x27);
                        played = TRUE;
                    }
                    input->state = 2;
                }
                if (func_ov021_020a751c(input, rightButton) && !played && menuState == 1) {
                    input->pressed &= ~rightButton;
                    input->held &= ~rightButton;
                    func_ov001_02078360(0, 1);
                    if (func_ov001_02078494() == 0) {
                        PlaySoundEffect_0204d924(0x1a0, 0x27);
                    }
                    input->state = 2;
                }
            } else if (func_ov021_020a751c(input, shortcutButton) && menuState == 0) {
                input->pressed &= ~shortcutButton;
                input->held &= ~shortcutButton;
                SelectFieldMenuEntryById_02077f3c(g_saveData_0205fe0c->shortcutEntry);
                if (!g_saveData_0205fe0c->controls.keepMenuOpen) {
                    input->pressed |= 0x400;
                    input->flags |= 1;
                }
                input->state = 2;
            }
            if (g_saveData_0205fe0c->controls.altControls && (input->state == 2 || input->timer == 0)) {
                input->unk_06 = 0;
            }
        } else {
            if (input->state != 0) {
                if (input->state == 1 && input->timer != 0 && func_ov001_02077ef4()) {
                    PlaySoundEffect_0204d924(0, 0);
                }
                input->state = 0;
            }
            func_ov001_020720cc(0);
        }
    } else {
        input->state = 0;
        func_ov001_020720cc(0);
    }

    if (func_ov001_02072040()) {
        u16 pressed = GetFieldAt0xc_020a7554(input);
        if (pressed) {
            input->command = 5;
            switch (func_ov001_02072020(pressed)) {
            case 1:
                subCommand = 4;
                break;
            case 0:
                subCommand = 1;
                break;
            case 2:
                subCommand = 3;
                break;
            case 4:
                subCommand = 2;
                break;
            default:
                subCommand = 0;
                break;
            }
            input->subCommand = subCommand;
        }
        input->pressed &= 0xf7fd;
        input->held &= 0xf7fd;
        input->pressed &= 0xff0f;
        input->held &= 0xff0f;
        input->unk_06 = 0;
    } else if (func_ov021_020a751c(input, 1)) {
        switch (func_ov001_02077bcc()) {
        case 0:
            input->command = 1;
            break;
        case 1:
        case 6:
        case 9:
            input->command = 2;
            break;
        case 2:
            input->command = 3;
            break;
        case 3:
            input->command = 4;
            break;
        case 13:
            input->command = 7;
            break;
        case 7:
            input->command = 1;
            break;
        case 8:
            input->command = 6;
            break;
        case 11:
            input->command = 8;
            break;
        }
    }

    switch (mode) {
    case 6:
        if (input->subCommand == 0 && func_ov001_02078494() == 2 && func_ov021_020a751c(input, 2)) {
            func_ov001_02078360(0, 1);
            input->pressed &= ~2;
            PlaySoundEffect_0204d924(0, 3);
        }
        break;
    case 7:
        if (input->subCommand == 0 && func_ov021_020a751c(input, 0x100)) {
            input->command = 1;
        }
        break;
    }
}
