#include "nitro/types.h"

typedef struct NameMenuParams {
    s32 initialSelection;
    s32 cancelSelection;
    s32 slotValues[0x16];
    s32 mode;
} NameMenuParams;

typedef struct Session {
    u8 pad_0000[0x27e8];
    void *nameMenu;
} Session;

extern Session *data_ov001_020a0460;
extern u8 data_ov001_0209ecdc[];
extern void func_01ff86fc(u32 value, void *destination, u32 size);
extern u8 func_ov001_02068918(s32 *output);
extern s32 func_ov001_02063a38(void);
extern BOOL func_ov035_020baf88(void);
extern BOOL SNDi_LockMutex_020baf94(void);
extern BOOL func_ov001_020645c8(u32 value);
extern void *func_0202a448(void *descriptor, void *userData);
extern void ShowSessionNameEntry_020639ac(int index);

void CreateSessionNameMenu_02063ba4(void) {
    Session *session = data_ov001_020a0460;
    NameMenuParams params;
    func_01ff86fc(0, &params, sizeof(params));
    func_ov001_02068918(params.slotValues);
    params.initialSelection = -1;
    params.cancelSelection = -1;
    switch (func_ov001_02063a38()) {
    case 4:
        params.mode = 1;
        break;
    case 7:
        params.mode = 3;
        break;
    case 6:
        params.mode = 2;
        if (func_ov035_020baf88()) {
            params.initialSelection = 1;
        }
        if (SNDi_LockMutex_020baf94()) {
            params.cancelSelection = 0;
        }
        break;
    default:
        if (func_ov001_020645c8(0x3609) || func_ov001_020645c8(0x360a)) {
            if (func_ov001_020645c8(0x3700)) {
                params.mode = 0;
            } else {
                params.mode = 4;
            }
        } else {
            params.mode = 0;
        }
        break;
    }
    session->nameMenu = func_0202a448(data_ov001_0209ecdc, &params);
    ShowSessionNameEntry_020639ac(-1);
}
