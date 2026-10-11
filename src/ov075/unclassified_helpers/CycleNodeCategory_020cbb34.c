#include "nitro/types.h"

typedef struct {
    u8 kind;
    u8 requiredLevel;
} CategoryInfo;

typedef struct {
    u16 id;
    u8 kind;
} GridEntry;

typedef struct {
    u8 pad_0000[0x98];
    u8 *columnCount;
} GridMap;

typedef struct {
    u8 pad_0000[0x2c67];
    u8 level;
} SaveData;

typedef struct {
    u8 pad_00000[0x28];
    u16 cursorX;
    u16 cursorY;
    u8 pad_0002c[0x70 - 0x2c];
    BOOL busy;
    BOOL scrolling;
    BOOL ready;
    u8 pad_0007c[0x88 - 0x7c];
    BOOL animating;
    u8 pad_0008c[0x12dc8 - 0x8c];
    BOOL menuOpen;
    u8 pad_12dcc[4];
    GridMap *map;
    GridEntry *current;
    u8 pad_12dd8[0x13e64 - 0x12dd8];
    u16 noticeTimer;
    u8 pad_13e66[0x13ea0 - 0x13e66];
    BOOL noticeActive;
    u8 pad_13ea4[0x17524 - 0x13ea4];
    BOOL transitioning;
} MatrixMenu;

extern CategoryInfo data_ov075_020d13ea[5];
extern SaveData *data_0205fe0c;
extern s32 GetDialogInputMode_020c42b4(MatrixMenu *menu);
extern GridEntry *FindPageEntryById_020ba348(GridMap *map, u32 id);
extern void ShowEntryHeaderMessage_020cad14(MatrixMenu *menu, GridEntry *entry);
extern BOOL ShowNextUnlockNotice_020cc9fc(MatrixMenu *menu, BOOL eventMode, BOOL queryOnly);
extern BOOL PlaySoundEffect_0204d924(int seqArcNo, int index);

void CycleNodeCategory_020cbb34(MatrixMenu *menu)
{
    CategoryInfo *table;
    u8 i;
    u8 level;
    BOOL isCategory;
    u8 kind;

    if (menu->ready == 0 || menu->menuOpen != 0 || menu->scrolling != 0 || menu->transitioning != 0 ||
        menu->animating != 0 || menu->noticeActive != 0 || menu->noticeTimer != 0 || menu->busy != 0 ||
        GetDialogInputMode_020c42b4(menu) != 0) {
        return;
    }
    isCategory = FALSE;
    kind = menu->current->kind;
    if (kind > 8 && kind < 0xe) {
        isCategory = TRUE;
    }
    if (!isCategory) {
        return;
    }
    table = data_ov075_020d13ea;
    level = data_0205fe0c->level;
    for (i = 0; i < 5; i++) {
        if (kind == table[i].kind) {
            do {
                i++;
                if (i == 5) {
                    i = 0;
                }
            } while (level < ((u8 *)table)[i * 2 + 1]);
            if (kind == table[i].kind) {
                return;
            }
            menu->current = FindPageEntryById_020ba348(menu->map, table[i].kind);
            menu->cursorX = menu->current->id % *menu->map->columnCount;
            menu->cursorY = menu->current->id / *menu->map->columnCount;
            ShowEntryHeaderMessage_020cad14(menu, menu->current);
            ShowNextUnlockNotice_020cc9fc(menu, TRUE, FALSE);
            PlaySoundEffect_0204d924(1, 2);
            return;
        }
    }
}
