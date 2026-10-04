#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x820];
    u8 counterChars[4];
} Ov081State;

typedef struct {
    u8 kind;
} EntryList;

extern const char data_ov081_020c5d40[];
extern const char data_ov081_020c5d50[];
extern void CountUnlockedListEntries_020c5460(Ov081State *state, EntryList *list, int *total, int *before);
extern void *func_0202e060(void *dst, const char *fmt, ...);
extern void DrawBgTextLabel_020c5530(void *charBase, int bg, const void *text, int x, int y, int areaWidth, int areaHeight, int tile);

void DrawListPageCounter_020c5654(Ov081State *state, EntryList *list)
{
    int total;
    int before;
    char text[12];

    if (list->kind == 1) {
        CountUnlockedListEntries_020c5460(state, list, &total, &before);
        func_0202e060(text, data_ov081_020c5d40, before + 1, total);
    } else {
        func_0202e060(text, data_ov081_020c5d50);
    }
    DrawBgTextLabel_020c5530(state->counterChars, 1, text, 0x1a, 1, 4, 2, 0x44);
}
