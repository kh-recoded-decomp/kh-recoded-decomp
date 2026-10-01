#include "nitro/types.h"

typedef struct MenuState {
    u8 kind;
    u8 pad_01[3];
    u32 target;
    u8 pad_08[0xc];
} MenuState;

extern BOOL func_ov059_020cd154(void);
extern BOOL func_ov001_020645c8(u32 bitOffset);
extern BOOL ReadActiveMenuState_0206c328(MenuState *out);
extern int func_ov001_0207f8f4(u32 target);
extern BOOL IsBattleModeNotTwo_02064280(void);
extern BOOL func_ov001_020642a0(void);
extern void SelectFieldMenuPage_02072064(int page);

void RefreshFieldMenuPage_0206d248(void)
{
    BOOL canOpen;
    int page;
    MenuState state;

    canOpen = FALSE;
    page = -1;
    if (func_ov059_020cd154() && !func_ov001_020645c8(0x3520)) {
        canOpen = TRUE;
    }
    if (ReadActiveMenuState_0206c328(&state)) {
        switch (state.kind) {
        case 0:
        case 4:
            break;
        case 2:
            switch (func_ov001_0207f8f4(state.target)) {
            case 0:
                if (canOpen) {
                    page = 0;
                }
                break;
            case 1:
                page = 1;
                break;
            case 2:
                page = 2;
                break;
            }
            break;
        case 1:
        case 3:
            if (canOpen) {
                page = 0;
            }
            break;
        }
    } else if (canOpen) {
        page = 0;
    }
    if (IsBattleModeNotTwo_02064280() && !func_ov001_020642a0()) {
        page = 3;
    }
    SelectFieldMenuPage_02072064(page);
}
