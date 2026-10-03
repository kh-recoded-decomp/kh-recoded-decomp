#include "nitro/types.h"
#include "nnsys/g2d.h"

typedef struct PanelInfo {
    u8 header[0x10];
    char name[0x57];
    u8 rank;
    u8 kind;
    u8 pad_69[7];
} PanelInfo;

typedef struct MenuState {
    u8 pad_00[0x9a];
    u8 phase9a : 2;
    u8 soundPlayed9a : 1;
    u8 highBits9a : 5;
    u8 pad_9b[0x301];
    u8 slots[0x100];
} MenuState;

extern MenuState *data_ov013_02074ce0;
extern char data_ov013_02074c70[];
extern char data_ov013_02074c80[];
extern char data_ov013_02074c94[];
extern char data_ov013_02074cac[];
extern char data_ov013_02074cc4[];

extern void func_01ff8684(int value, void *dst, int size);
extern int DispatchContextCommand_02066c78(int command, int value, int extra, void *buffer);
extern s32 func_ov013_02070cb4(void);
extern char *func_ov002_020621c4(int index, int extra);
extern void *OS_SNPrintf_0202e080(char *dst, unsigned int len, const char *fmt, ...);
extern u32 func_0202b788(void);
extern void func_ov002_02061b74(int param1, int p2, int p3, int p4, int p5, int p6, int p7, char *text);
extern void func_ov002_02061dc8(int selectSecond, int arg2, int arg3, int arg4, int arg5, int arg6, char *text, int arg8);
extern void func_ov002_020619e8(int param1, int x, int y, int color, const void *value);
extern NNSG2dTextRect MeasurePanelTextPrimary_020627e8(int which, const u16 *text);
extern int CountFlaggedCategorySelections_0206a45c(void *selection);
extern int CountFilledCategorySelections_0206a678(void *selection);
extern BOOL PlaySoundEffect_0204d924(int seqArcNo, int index);
extern int *func_ov027_020b90a4(void *entries, int index);
extern void SetEntrySlotsVisible_020b9580(void *entries, int *slot, int visible);

void DrawContextEntrySummary_0206eb18(void) {
    u16 text[0x40] = {0};
    u16 title[0x40] = {0};
    PanelInfo info;
    NNSG2dTextRect rect;
    char *label;
    char *count;
    MenuState *state;

    func_ov002_02061b74(1, 0, 2, 0xf0, 0x10, 10, 0x800, func_ov002_020621c4(0x3a, 0));
    func_01ff8684(0, text, sizeof(text));
    DispatchContextCommand_02066c78(0, func_ov013_02070cb4(), 0, &info);
    OS_SNPrintf_0202e080((char *)title, 0x40, func_ov002_020621c4(0x1e, 0), info.name);
    switch (func_0202b788()) {
    case 3:
        label = func_ov002_020621c4(info.kind + 0x18, 0);
        count = func_ov002_020621c4(0x1f, 0);
        OS_SNPrintf_0202e080((char *)text, 0x40, data_ov013_02074c70, (char *)title, label, count);
        break;
    case 1:
        label = func_ov002_020621c4(info.kind + 0x18, 0);
        count = func_ov002_020621c4(0x1f, 0);
        OS_SNPrintf_0202e080((char *)text, 0x40, data_ov013_02074c80, (char *)title, label, count);
        break;
    case 2:
        count = func_ov002_020621c4(0x1f, 0);
        label = func_ov002_020621c4(info.kind + 0x18, 0);
        OS_SNPrintf_0202e080((char *)text, 0x40, data_ov013_02074c80, count, label, (char *)title);
        break;
    case 5:
        count = func_ov002_020621c4(0x1f, 0);
        label = func_ov002_020621c4(info.kind + 0x18, 0);
        OS_SNPrintf_0202e080((char *)text, 0x40, data_ov013_02074c94, count, label, (char *)title);
        break;
    case 4:
        count = func_ov002_020621c4(0x1f, 0);
        label = func_ov002_020621c4(info.kind + 0x18, 0);
        OS_SNPrintf_0202e080((char *)text, 0x40, data_ov013_02074cac, count, label, (char *)title);
        break;
    case 0:
    default:
        label = func_ov002_020621c4(info.kind + 0x18, 0);
        count = func_ov002_020621c4(0x1f, 0);
        OS_SNPrintf_0202e080((char *)text, 0x40, data_ov013_02074cc4, (char *)title, label, count);
        break;
    }
    func_ov002_02061dc8(1, 0x80, 0x23, 2, 6, 2, (char *)text, 0);
    rect = MeasurePanelTextPrimary_020627e8(1, (u16 *)func_ov002_020621c4(info.rank + 0x40, 0));
    func_ov002_020619e8(1, 0xe, 0x6f - rect.height / 2, 0xc, func_ov002_020621c4(info.rank + 0x40, 0));
    OS_SNPrintf_0202e080((char *)text, 0x40, func_ov002_020621c4(0x16, 0),
        CountFlaggedCategorySelections_0206a45c(&info), CountFilledCategorySelections_0206a678(&info));
    func_ov002_02061b74(0, 0xb4, 100, 0x40, 10, 2, 0x411, (char *)text);
    if (DispatchContextCommand_02066c78(5, 0, 0, 0)) {
        state = data_ov013_02074ce0;
        SetEntrySlotsVisible_020b9580(state->slots, func_ov027_020b90a4(state->slots, 4), 1);
        data_ov013_02074ce0->phase9a = 2;
        if (!data_ov013_02074ce0->soundPlayed9a) {
            PlaySoundEffect_0204d924(2, 0xd);
            data_ov013_02074ce0->soundPlayed9a = 1;
        }
    }
}
