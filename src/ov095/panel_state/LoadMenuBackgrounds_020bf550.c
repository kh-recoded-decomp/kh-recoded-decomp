#include "nitro/types.h"

typedef struct ScreenData {
    u16 width;
    u16 height;
} ScreenData;

typedef struct CharacterData {
    u8 pad_00[0x10];
    u32 size;
} CharacterData;

typedef struct BgGraphicsData {
    ScreenData *screen;
    CharacterData *character;
    void *palette;
} BgGraphicsData;

typedef struct {
    int ids[7];
} TileIdList7;

typedef struct {
    int ids[2];
} TileIdList2;

typedef struct {
    u8 pad_000[8];
    u32 archiveBase;
    u32 sharedArchiveBase;
    u8 pad_010[0x120];
    void *frameArchive;
    BgGraphicsData frameBg;
    void *panelArchive;
    BgGraphicsData panelBg;
    void *tabArchive;
    BgGraphicsData tabBg;
    void *overlayArchive;
    BgGraphicsData overlayBg;
    void *sharedArchive;
    BgGraphicsData sharedBg;
} MenuBgScene;

#define ARCHIVE_FILE(base, index) ((((base) + 0x8000) & 0xfffffc) << 7 | 0x80000000 | (index))

extern TileIdList7 data_ov095_020c1708;
extern TileIdList2 data_ov095_020c16f4;
extern void *func_0202c478(u32 fileId, int heapId);
extern void GetBgDataFromArchive_0202b554(BgGraphicsData *out, void *archive, int screenIndex, int characterIndex,
                                          int paletteIndex);
extern void DispatchByPartType_0202b4c0(int part, void *screen, void *character, void *palette, int arg4, int arg5);
extern int Gfx_EnqueueTableCmdAt14_0202b448(int idx, void *p, int arg2, int arg3);
extern void func_ov095_020bf444(ScreenData *dst, ScreenData *src, int fromTile, int toTile, int palette, int tile,
                                int width, int height, int stepX, int stepY);

void LoadMenuBackgrounds_020bf550(MenuBgScene *scene)
{
    TileIdList7 panelTiles;
    TileIdList2 tabTiles;
    ScreenData *screen;
    int i;
    int width;
    int height;

    scene->frameArchive = func_0202c478(ARCHIVE_FILE(scene->archiveBase, 0x2e), 0xe);
    GetBgDataFromArchive_0202b554(&scene->frameBg, scene->frameArchive, 0, 0, 0);
    DispatchByPartType_0202b4c0(2, scene->frameBg.screen, scene->frameBg.character, scene->frameBg.palette, 0x1c, 0);

    scene->panelArchive = func_0202c478(ARCHIVE_FILE(scene->archiveBase, 0x2f), 0xe);
    GetBgDataFromArchive_0202b554(&scene->panelBg, scene->panelArchive, 0, 0, 0);
    screen = scene->panelBg.screen;
    width = (u32)screen->width >> 3;
    height = (u32)screen->height >> 3;
    panelTiles = data_ov095_020c1708;
    for (i = 0; i < 7; i++) {
        func_ov095_020bf444(screen, screen, 0xd, panelTiles.ids[i], 0xe, panelTiles.ids[i], width, height, 3, 3);
    }
    DispatchByPartType_0202b4c0(3, scene->panelBg.screen, scene->panelBg.character, scene->panelBg.palette, 0x1e, 0);

    scene->tabArchive = func_0202c478(ARCHIVE_FILE(scene->archiveBase, 0x30), 0xe);
    GetBgDataFromArchive_0202b554(&scene->tabBg, scene->tabArchive, 0, 0, 0);
    {
        ScreenData *tabScreen = scene->tabBg.screen;
        int j;
        int tabWidth = (u32)tabScreen->width >> 3;
        int tabHeight = (u32)tabScreen->height >> 3;

        tabTiles = data_ov095_020c16f4;
        for (j = 0; j < 2; j++) {
            func_ov095_020bf444(tabScreen, tabScreen, 0xd, tabTiles.ids[j], 0xe, tabTiles.ids[j], tabWidth, tabHeight,
                                3, 3);
        }
    }

    *(vu32 *)0x0400001c = 0x1e00000;

    scene->sharedArchive = func_0202c478(ARCHIVE_FILE(scene->sharedArchiveBase, 0), 0xe);
    GetBgDataFromArchive_0202b554(&scene->sharedBg, scene->sharedArchive, 0, 0, 0);
    Gfx_EnqueueTableCmdAt14_0202b448(1, scene->sharedBg.character, 0, scene->sharedBg.character->size);

    scene->overlayArchive = func_0202c478(ARCHIVE_FILE(scene->archiveBase, 0x2c), 0xe);
    GetBgDataFromArchive_0202b554(&scene->overlayBg, scene->overlayArchive, 0, 0, 0);
    DispatchByPartType_0202b4c0(4, scene->overlayBg.screen, scene->overlayBg.character, scene->overlayBg.palette, 0x1f,
                                0);
}












