#include "nitro/types.h"

typedef struct {
    u8 pad_00[0xa20];
    u8 titleChars[0x63c6 - 0xa20];
    s8 cursor;
} Ov081State;

typedef struct {
    u8 kind;
    u8 id;
    u8 pad_02[2];
    u8 *ids;
} EntryList;

extern const u16 *func_ov081_020c5be4(int id);
extern void DrawBgTextLabel_020c5530(void *charBase, int bg, const void *text, int x, int y, int areaWidth, int areaHeight, int tile);

void DrawListTitle_020c56a8(Ov081State *state, EntryList *list)
{
    switch (list->kind) {
    case 0:
        DrawBgTextLabel_020c5530(state->titleChars, 1, func_ov081_020c5be4(list->id), 2, 3, 0x1d, 0xc, 0x4c);
        break;
    case 1:
        DrawBgTextLabel_020c5530(state->titleChars, 1, func_ov081_020c5be4(list->ids[state->cursor]), 2, 3, 0x1d, 0xc, 0x4c);
        break;
    }
}
