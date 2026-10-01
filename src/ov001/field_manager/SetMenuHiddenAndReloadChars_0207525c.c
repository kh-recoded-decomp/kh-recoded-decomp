#include "nitro/types.h"

typedef struct CharUpload {
    u32 offset;
    u32 size;
    u32 unk_08;
} CharUpload;

typedef struct MenuState {
    void *charData[3];
    u8 pad_0c[0x14];
    void *cursorChars;
    u8 pad_24[8];
    int hidden;
} MenuState;

extern MenuState *data_ov001_020a04ac;
extern const CharUpload data_ov001_0209edd0[3];
extern void GX_LoadBG3Char_02007b70(const void *src, u32 offset, u32 size);

void SetMenuHiddenAndReloadChars_0207525c(int hidden)
{
    MenuState *menu = data_ov001_020a04ac;
    int i;

    menu->hidden = hidden;
    if (hidden == 0) {
        for (i = 0; i < 3; i++) {
            if (menu->charData[i] != NULL) {
                GX_LoadBG3Char_02007b70(menu->charData[i], data_ov001_0209edd0[i].offset, data_ov001_0209edd0[i].size);
            }
        }
        GX_LoadBG3Char_02007b70(menu->cursorChars, 0x9e0, 0x40);
    }
}
