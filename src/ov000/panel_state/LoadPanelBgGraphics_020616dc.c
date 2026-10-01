#include "nitro/types.h"

typedef struct BgGraphicsData {
    void *screen;
    void *character;
    void *palette;
} BgGraphicsData;

typedef struct BgScreenPair {
    BgGraphicsData main;
    BgGraphicsData sub;
} BgScreenPair;

typedef struct BgIndexEntry {
    int mainIndex;
    int subIndex;
    int mainPalette;
    int subPalette;
} BgIndexEntry;

typedef struct BgIndexTable {
    BgIndexEntry entries[5];
} BgIndexTable;

typedef struct Panel {
    u32 resourceId;
    u32 bgResourceId;
    u8 pad_08[0x198];
    void *bgArchive;
    BgScreenPair screens[5];
    void *mainCharFile;
    void *subCharFile;
} Panel;

extern const BgIndexTable data_ov000_020637d4;

extern void *func_0202c478(u32 fileId, u32 param2);
extern void GetBgDataFromArchive_0202b554(BgGraphicsData *out, void *archive, int screenIndex, int characterIndex,
                                          int paletteIndex);
extern BOOL func_02014d38(void *file, void **characterOut);

void LoadPanelBgGraphics_020616dc(Panel *panel)
{
    BgIndexTable table = data_ov000_020637d4;
    int i;

    panel->bgArchive = func_0202c478(((panel->resourceId + 0x8000) & 0xfffffc) << 7 | 0x80000001, 0xe);
    panel->mainCharFile = func_0202c478(((panel->bgResourceId + 0x8000) & 0xfffffc) << 7 | 0x80000000, 0xe);
    panel->subCharFile = func_0202c478(((panel->bgResourceId + 0x8000) & 0xfffffc) << 7 | 0x80000002, 0xe);

    for (i = 0; i < 5; i++) {
        GetBgDataFromArchive_0202b554(&panel->screens[i].main, panel->bgArchive, table.entries[i].mainIndex,
                                      table.entries[i].mainIndex, table.entries[i].mainPalette);
        GetBgDataFromArchive_0202b554(&panel->screens[i].sub, panel->bgArchive, table.entries[i].subIndex,
                                      table.entries[i].subIndex, table.entries[i].subPalette);
    }

    func_02014d38(panel->mainCharFile, &panel->screens[3].main.character);
    func_02014d38(panel->subCharFile, &panel->screens[3].sub.character);

    panel->screens[1].main.palette = panel->screens[0].main.palette;
    panel->screens[1].sub.palette = panel->screens[0].sub.palette;
    panel->screens[2].main.palette = panel->screens[0].main.palette;
    panel->screens[2].sub.palette = panel->screens[0].sub.palette;
    panel->screens[3].main.palette = panel->screens[0].main.palette;
    panel->screens[3].sub.palette = panel->screens[0].sub.palette;
}
