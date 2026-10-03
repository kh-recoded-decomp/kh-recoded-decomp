#include "nitro/types.h"

typedef struct {
    u8 pad_000[0x19];
    u8 levelA;
    u8 levelB;
    u8 pad_01b[0x339];
    void *messages;
} Work;

typedef struct {
    u8 pad_00[0x10];
    u8 selection;
} SelectionRecord;

extern int data_ov035_020bc4e0;
extern char data_ov041_020cf948[];
extern void *Msg_OpenContainerAndReadHeader_0202cc6c(const char *name, u32 mode, BOOL allocFromEnd);
extern BOOL func_ov041_020bec60(int id);
extern SelectionRecord *GetOverlaySelectionRecord(int index);
extern void func_ov041_020bddfc(int index, u8 level);

void InitResourceLevels_020bdc6c(void) {
    Work *work;
    int i;
    int level;

    work = *(Work **)(data_ov035_020bc4e0 + 0xb8);
    work->messages = Msg_OpenContainerAndReadHeader_0202cc6c(data_ov041_020cf948, 0x12, FALSE);
    for (i = 0; i < 0x3e; i++) {
        level = 0;
        switch (i) {
        case 0:
            level = 1;
            break;
        case 1:
            level = work->levelB;
            break;
        case 2:
            level = 2;
            break;
        case 3:
            level = 2;
            break;
        case 4:
            level = 3;
            break;
        case 5:
            level = 3;
            break;
        case 6:
            level = 3;
            break;
        case 7:
            level = work->levelB;
            break;
        case 8:
            level = work->levelB;
            break;
        case 9:
            level = work->levelB;
            break;
        case 10:
            level = work->levelB;
            break;
        case 12:
            if (func_ov041_020bec60(5) || func_ov041_020bec60(0xc) || func_ov041_020bec60(0xe) ||
                func_ov041_020bec60(0xf) || func_ov041_020bec60(0x17)) {
                level = 1;
            }
            break;
        case 13:
            if (func_ov041_020bec60(6) || func_ov041_020bec60(0xe) || func_ov041_020bec60(0xf)) {
                level = 1;
            }
            break;
        case 14:
            if (func_ov041_020bec60(4) || func_ov041_020bec60(0xe)) {
                level = 1;
            }
            break;
        case 15:
        case 16:
        case 17:
        case 50:
            level = work->levelA > work->levelB ? work->levelA : work->levelB;
            break;
        case 18:
            level = work->levelA;
            break;
        case 19:
            level = work->levelA;
            break;
        case 20:
            level = 1;
            break;
        case 21:
            level = 3;
            break;
        case 22:
            level = 1;
            break;
        case 23:
        case 24:
        case 25:
        case 26:
        case 27:
        case 28:
        case 29:
        case 31:
        case 32:
        case 33:
        case 34:
        case 35:
        case 37:
        case 38:
        case 39:
        case 40:
        case 41:
        case 42:
        case 43:
        case 44:
            level = 1;
            break;
        case 36:
            level = 2;
            break;
        case 30:
            level = work->levelA;
            break;
        case 45:
            level = 1;
            break;
        case 46:
            level = 2;
            break;
        case 47:
            level = 1;
            break;
        case 48:
            level = 1;
            break;
        case 49:
            level = 3;
            break;
        case 51:
        case 52:
        case 53:
        case 54:
        case 55:
        case 56:
        case 57:
        case 58:
        case 59:
        case 60:
        case 61:
            if (i - 51 == GetOverlaySelectionRecord(0)->selection) {
                level = 2;
            }
            break;
        }
        if (level > 0) {
            func_ov041_020bddfc(i, level);
        }
    }
}
