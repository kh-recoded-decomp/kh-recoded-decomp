#include "nitro/types.h"

typedef struct MovieMenu {
    u8 pad_00[0x1c];
    int cursorY;
    u8 pad_20[0x12];
    u8 row;
} MovieMenu;

typedef struct MovieMenuState {
    void *unk_00;
    MovieMenu *menu;
} MovieMenuState;

extern MovieMenuState data_ov035_020bc4e8;

void SetMovieMenuRow_020bc1d4(int row)
{
    data_ov035_020bc4e8.menu->row = row;
    data_ov035_020bc4e8.menu->cursorY = 0xb0 - (row - 1) * 16;
}