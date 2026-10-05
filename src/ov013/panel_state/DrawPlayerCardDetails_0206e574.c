#include "nitro/types.h"

typedef struct TextRect {
    int width;
    int height;
} TextRect;

typedef struct CardDate {
    u16 year : 7;
    u16 month : 4;
    u16 day : 5;
} CardDate;

typedef struct PlayerCard {
    u8 header[0x10];
    u16 name[0xb];
    u16 message[0x1b];
    CardDate date;
    u8 pad_5e[7];
    u8 titleId;
    u8 level;
    u8 rank;
    u8 avatarFrame;
    u8 pad_69[3];
    u8 capitalize;
    u8 pad_6d[3];
} PlayerCard;

typedef struct MenuState {
    u8 pad_00[0x9a];
    u8 phase9a : 2;
    u8 soundPlayed9a : 1;
    u8 highBits9a : 5;
    u8 pad_9b[0x2f0 - 0x9b];
    s8 progress;
    u8 pad_2f1[0x39c - 0x2f1];
    u8 objMain[0x100];
} MenuState;

extern MenuState *data_ov013_02074ce0;

extern void func_ov002_0206203c(int selector);
extern int DispatchContextCommand_02066c78(int command, int value, int extra, void *buffer);
extern s32 func_ov013_02070cb4(void);
extern char *func_ov002_020621c4(int index, int extra);
extern void *OS_SNPrintf_0202e080(u16 *dst, unsigned int len, const char *fmt, ...);
extern u32 func_0202b788(void);
extern u16 *CopyWideStringCapitalized_02066430(u16 *dst, const u16 *src, int size);
extern u16 *CopyWideStringWithNewline_02066484(u16 *dst, int size, const u16 *src, int breakIndex);
extern void func_ov002_02061b74(int param1, int p2, int p3, int p4, int p5, int p6, int p7, u16 *text);
extern void func_ov002_02061dc8(int selectSecond, int arg2, int arg3, int arg4, int arg5, int arg6, char *text, int arg8);
extern void func_ov002_020619e8(int param1, int x, int y, int color, const void *value);
extern TextRect MeasurePanelTextPrimary_020627e8(int which, const void *text);
extern int CountFlaggedCategorySelections_0206a45c(void *selection);
extern int CountFilledCategorySelections_0206a678(void *selection);
extern BOOL PlaySoundEffect_0204d924(int seqArcNo, int index);
extern void StopSeqArcOrDefault_0204d960(int seqArcNo, int index, int fadeFrames);
extern int *func_ov027_020b90a4(void *entries, int index);
extern void func_ov027_020b9580(void *entries, int *slot, BOOL visible);
extern void func_ov027_020b96a0(void *entries, int *slot, int frame);

void DrawPlayerCardDetails_0206e574(void)
{
    u16 text[0x40] = {0};
    PlayerCard card;
    TextRect rect;
    CardDate date;
    int tens;
    int progress;
    void *container;

    func_ov002_0206203c(-1);
    progress = data_ov013_02074ce0->progress + 1;
    if (progress % 10 != 0) {
        *(vu32 *)0x04000000 = (*(vu32 *)0x04000000 & ~0x1f00) | 0x1e00;
        DispatchContextCommand_02066c78(0, func_ov013_02070cb4(), 0, &card);
        if (func_0202b788() == 1) {
            if (card.capitalize) {
                func_ov002_020619e8(1, 0x1c, 0x20, 2, CopyWideStringCapitalized_02066430(text, card.name, 0x80));
            } else {
                func_ov002_020619e8(1, 0x1c, 0x20, 2, card.name);
            }
        } else {
            func_ov002_020619e8(1, 0x1c, 0x20, 2, card.name);
        }
        func_ov002_020619e8(1, 0x16, 0x51, 0xc, CopyWideStringWithNewline_02066484(text, 0x80, card.message, 0xd));
        rect = MeasurePanelTextPrimary_020627e8(1, func_ov002_020621c4(card.rank + 0x40, 0));
        func_ov002_020619e8(1, 0x52, 0x9c - rect.height / 2, 2, func_ov002_020621c4(card.rank + 0x40, 0));
        container = data_ov013_02074ce0->objMain;
        func_ov027_020b96a0(container, func_ov027_020b90a4(container, 10), card.avatarFrame);
        container = data_ov013_02074ce0->objMain;
        func_ov027_020b96a0(container, func_ov027_020b90a4(container, 0x14), (u16)(card.level % 10));
        tens = card.level / 10 % 10;
        if (tens != 0) {
            container = data_ov013_02074ce0->objMain;
            func_ov027_020b96a0(container, func_ov027_020b90a4(container, 0x15), (u16)tens);
            container = data_ov013_02074ce0->objMain;
            func_ov027_020b9580(container, func_ov027_020b90a4(container, 0x15), TRUE);
        } else {
            container = data_ov013_02074ce0->objMain;
            func_ov027_020b9580(container, func_ov027_020b90a4(container, 0x15), FALSE);
        }
        if (DispatchContextCommand_02066c78(5, 0, 0, 0)) {
            container = data_ov013_02074ce0->objMain;
            func_ov027_020b9580(container, func_ov027_020b90a4(container, 8), TRUE);
            data_ov013_02074ce0->phase9a = 1;
            if (DispatchContextCommand_02066c78(5, 0, 0, 0) && !data_ov013_02074ce0->soundPlayed9a) {
                PlaySoundEffect_0204d924(2, 0xd);
                data_ov013_02074ce0->soundPlayed9a = 1;
            }
        }
        date = card.date;
        switch (func_0202b788()) {
        case 0:
            OS_SNPrintf_0202e080(text, 0x40, func_ov002_020621c4(0x17, 0), date.year, date.month, date.day);
            break;
        case 1:
            OS_SNPrintf_0202e080(text, 0x40, func_ov002_020621c4(0x17, 0), date.month, date.day, date.year + 2000);
            break;
        default:
            OS_SNPrintf_0202e080(text, 0x40, func_ov002_020621c4(0x17, 0), date.day, date.month, date.year + 2000);
            break;
        }
        switch (func_0202b788()) {
        case 3:
            func_ov002_02061b74(1, 0, 0xb5, 0xfa, 0x10, 0xc, 0x800, text);
            break;
        default:
            func_ov002_02061b74(1, 0, 0xb6, 0xfa, 0x10, 0xc, 0x800, text);
            break;
        }
        func_ov002_020619e8(1, 0x1c, 0x14, 10, func_ov002_020621c4(card.titleId, 0));
        OS_SNPrintf_0202e080(text, 0x40, func_ov002_020621c4(0x16, 0), CountFlaggedCategorySelections_0206a45c(&card),
                             CountFilledCategorySelections_0206a678(&card));
        func_ov002_020619e8(0, 0xbe, 0x5c, 2, text);
    } else {
        func_ov002_02061dc8(1, 0x80, 0x4b, 2, 6, 10, func_ov002_020621c4(progress / 10 % 11 + 0x5f, 0), 0);
        *(vu32 *)0x04000000 = (*(vu32 *)0x04000000 & ~0x1f00) | 0x1d00;
        container = data_ov013_02074ce0->objMain;
        func_ov027_020b9580(container, func_ov027_020b90a4(container, 8), FALSE);
        if (data_ov013_02074ce0->soundPlayed9a == 1) {
            StopSeqArcOrDefault_0204d960(2, 0xd, 4);
            data_ov013_02074ce0->soundPlayed9a = 0;
        }
    }
}
