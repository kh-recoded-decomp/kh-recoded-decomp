#include "nitro/types.h"
#include "src/overlays/ov041/StageWork.h"

#define PAD_BUTTON_B 0x0002
#define PAD_KEY_RIGHT 0x0010
#define PAD_KEY_LEFT 0x0020
#define PAD_KEY_UP 0x0040
#define PAD_KEY_DOWN 0x0080
#define PAD_BUTTON_L 0x0200
#define PAD_BUTTON_X 0x0400
#define PAD_BUTTON_Y 0x0800

/* The shortcut options of the save's settings word. */
typedef struct ShortcutSettings {
    u8 reserved0000[0x2878];
    u32 reservedBits : 8;
    u32 keepDirections : 1;
    u32 useDirectionPad : 1;
} ShortcutSettings;

extern ShortcutSettings *data_0205fe0c;
extern u16 data_02060500;
extern u16 data_020604fc;
extern BOOL func_ov001_02077ef4(void);
extern BOOL func_ov001_02077e68(void);
extern int func_ov001_02078494(void);
extern void SetFieldMenuMode_02078360(int mode, int animate);
extern void PlayStageSound(int seqArcNo, int index, BOOL checked);

/*
 * Command menu shortcuts, all behind L: pressing L arms them; while L is held the next and previous buttons
 * (B and X, or down and up with the direction pad option, swapped unless the directions are kept) move through
 * the menu, and when canSwitchMode is set Y (or right and left) opens or closes the second menu mode. Letting go
 * of L without using a shortcut moves to the next entry.
 */
void HandleCommandMenuShortcuts(BOOL canSwitchMode)
{
    u16 previous;
    u16 next;
    u16 modifier;
    u16 openMode;
    u16 closeMode;
    StageWork *work = gMovieContextState->stageWork;
    ShortcutSettings *settings = data_0205fe0c;

    if (!settings->useDirectionPad) {
        modifier = PAD_BUTTON_L;
        previous = PAD_BUTTON_X;
        next = PAD_BUTTON_B;
        openMode = PAD_BUTTON_Y;
        closeMode = PAD_BUTTON_Y;
    } else {
        modifier = PAD_BUTTON_L;
        previous = PAD_KEY_UP;
        next = PAD_KEY_DOWN;
        openMode = PAD_KEY_RIGHT;
        closeMode = PAD_KEY_LEFT;
    }
    if (!settings->keepDirections) {
        u16 swap = previous;
        previous = next;
        next = swap;
    }
    if (data_02060500 & modifier) {
        work->stateTimer = 1;
        return;
    }
    if (data_020604fc & modifier) {
        if (data_02060500 & next) {
            work->stateTimer = 2;
            if (func_ov001_02077ef4()) {
                PlayStageSound(0, 0, FALSE);
            }
            return;
        }
        if (data_02060500 & previous) {
            work->stateTimer = 2;
            if (func_ov001_02077e68()) {
                PlayStageSound(0, 0, FALSE);
            }
            return;
        }
        if (canSwitchMode && func_ov001_02078494() == 0 && (data_02060500 & openMode)) {
            SetFieldMenuMode_02078360(1, 1);
            if (func_ov001_02078494() == 1) {
                work->stateTimer = 2;
                PlayStageSound(0x1a0, 0x27, FALSE);
            }
            return;
        }
        if (canSwitchMode && func_ov001_02078494() == 1 && (data_02060500 & closeMode)) {
            SetFieldMenuMode_02078360(0, 1);
            if (func_ov001_02078494() == 0) {
                work->stateTimer = 2;
                PlayStageSound(0x1a0, 0x27, FALSE);
            }
        }
    } else if (work->stateTimer == 1) {
        work->stateTimer = 0;
        if (func_ov001_02077ef4()) {
            PlayStageSound(0, 0, FALSE);
        }
    }
}
