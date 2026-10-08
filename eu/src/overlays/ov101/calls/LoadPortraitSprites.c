#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    s16 frameWidth;
    s16 frameHeight;
    s16 width;
    s16 height;
    u8 pad_08[8];
    fx32 x;
    fx32 y;
    u8 pad_18[8];
    int scale;
    u8 visible;
    u8 pad_25[5];
    u8 alpha : 5;
    u8 flags : 3;
    u8 pad_2B[5];
} SpriteDesc;

typedef struct {
    u32 fileIndex;
    u8 pad_04[8];
} IconEntry;

typedef struct {
    IconEntry entries[30];
    u8 pad_168[8];
} IconTable;

typedef struct {
    s32 mode;
    u8 pad_0004[0x30];
    u32 archive;
    u8 pad_0038[0xCE04 - 0x38];
    SpriteDesc mainSprite;
    SpriteDesc extraSprite;
    s32 spriteCount;
    s32 selection[17];
} Ov101State;

extern const IconTable data_ov101_020c1f9c[];
extern void NNS_GfdResetFrmTexVramState(void);
extern void NNS_GfdResetFrmPlttVramState(void);
extern BOOL InitSlotFromFile(SpriteDesc *slot, u32 fileId);

#define ARCHIVE_FILE_ID(archive, index) (((((archive) + 0x8000) & 0xfffffc) << 7) | 0x80000000 | ((index) & 0x1ff))

void LoadPortraitSprites(Ov101State *state)
{
    int mode = state->mode;
    SpriteDesc *sprite = &state->mainSprite;
    int selection = state->selection[mode];

    NNS_GfdResetFrmTexVramState();
    NNS_GfdResetFrmPlttVramState();
    InitSlotFromFile(sprite, ARCHIVE_FILE_ID(state->archive, data_ov101_020c1f9c[mode].entries[selection].fileIndex));
    sprite->scale = 0;
    sprite->visible = 1;
    sprite->alpha = 0x1f;
    sprite->width = sprite->frameWidth;
    sprite->height = sprite->frameHeight;
    sprite->x = 0;
    sprite->y = 0;
    state->spriteCount++;
    if (mode != 0x10) {
        return;
    }
    sprite = &state->extraSprite;
    InitSlotFromFile(sprite, ARCHIVE_FILE_ID(state->archive, selection + 0xc7));
    sprite->scale = 0x1000;
    sprite->visible = 1;
    sprite->alpha = 0x1f;
    sprite->width = sprite->frameWidth;
    sprite->height = sprite->frameHeight;
    sprite->x = 0;
    sprite->y = 0;
    state->spriteCount++;
}

