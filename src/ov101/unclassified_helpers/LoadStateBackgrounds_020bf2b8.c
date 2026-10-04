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
    u8 pad_000[0x1C];
    s32 mainHandle;
    s32 subHandle;
    u8 pad_024[0x14C - 0x24];
    void *mainArchive;
    BgGraphicsData mainBg;
    void *overlayArchive;
    BgGraphicsData overlayBg;
    void *subArchive;
    BgGraphicsData subBg;
} Ov101State;

extern void *func_0202c478(u32 fileId, u32 kind);
extern void GetBgDataFromArchive_0202b554(BgGraphicsData *out, void *archive, int screenIndex, int characterIndex,
                                          int paletteIndex);
extern void DispatchByPartType_0202b4c0(int partType, void *screen, CharacterData *character, void *palette,
                                        int mask, int flag);
extern int Gfx_EnqueueTableCmdAt14_0202b448(int index, CharacterData *character, int offset, u32 size);

void LoadStateBackgrounds_020bf2b8(Ov101State *state)
{
    state->mainArchive = func_0202c478(((state->mainHandle + 0x8000U) & 0xfffffc) << 7 | 0x80000002, 0xe);
    GetBgDataFromArchive_0202b554(&state->mainBg, state->mainArchive, 0, 0, 0);
    DispatchByPartType_0202b4c0(2, state->mainBg.screen, state->mainBg.character, state->mainBg.palette, 0x1f, 0);

    state->subArchive = func_0202c478(((state->subHandle + 0x8000U) & 0xfffffc) << 7 | 0x80000000, 0xe);
    GetBgDataFromArchive_0202b554(&state->subBg, state->subArchive, 0, 0, 0);
    Gfx_EnqueueTableCmdAt14_0202b448(2, state->subBg.character, 0xc00, state->subBg.character->size);

    state->overlayArchive = func_0202c478(((state->mainHandle + 0x8000U) & 0xfffffc) << 7 | 0x80000000, 0xe);
    GetBgDataFromArchive_0202b554(&state->overlayBg, state->overlayArchive, 0, 0, 0);
    DispatchByPartType_0202b4c0(4, state->overlayBg.screen, state->overlayBg.character, state->overlayBg.palette,
                                0x1f, 0);
}
