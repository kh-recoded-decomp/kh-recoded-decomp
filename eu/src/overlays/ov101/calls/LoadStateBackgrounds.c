#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x10];
    u32 size;
    void *data;
} CharacterData;

typedef struct {
    void *screen;
    CharacterData *character;
    void *palette;
} BgGraphicsData;

typedef struct {
    u8 pad_000[0x24];
    s32 mainHandle;
    s32 subHandle;
    u8 pad_02C[0x154 - 0x2C];
    void *mainArchive;
    BgGraphicsData mainBg;
    void *overlayArchive;
    BgGraphicsData overlayBg;
    void *subArchive;
    BgGraphicsData subBg;
} Ov101State;

extern void *Archive_LoadFile(u32 fileId, u32 kind);
extern void GetBgDataFromArchive(BgGraphicsData *out, void *archive, int screenIndex, int characterIndex,
                                 int paletteIndex);
extern void DispatchByPartType(int partType, void *screen, CharacterData *character, void *palette,
                               int mask, int flag);
extern int Gfx_EnqueueTableCmdAt14(int index, CharacterData *character, int offset, u32 size);

void LoadStateBackgrounds(Ov101State *state)
{
    state->mainArchive = Archive_LoadFile(((state->mainHandle + 0x8000U) & 0xfffffc) << 7 | 0x80000002, 0xe);
    GetBgDataFromArchive(&state->mainBg, state->mainArchive, 0, 0, 0);
    DispatchByPartType(2, state->mainBg.screen, state->mainBg.character, state->mainBg.palette, 0x1f, 0);

    state->subArchive = Archive_LoadFile(((state->subHandle + 0x8000U) & 0xfffffc) << 7 | 0x80000000, 0xe);
    GetBgDataFromArchive(&state->subBg, state->subArchive, 0, 0, 0);
    Gfx_EnqueueTableCmdAt14(2, state->subBg.character, 0xc00, state->subBg.character->size);

    state->overlayArchive = Archive_LoadFile(((state->mainHandle + 0x8000U) & 0xfffffc) << 7 | 0x80000000, 0xe);
    GetBgDataFromArchive(&state->overlayBg, state->overlayArchive, 0, 0, 0);
    DispatchByPartType(4, state->overlayBg.screen, state->overlayBg.character, state->overlayBg.palette,
                       0x1f, 0);
}
