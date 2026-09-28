#include "nitro/types.h"

typedef struct BgGraphicsData {
    void *screen;
    void *character;
    void *palette;
} BgGraphicsData;

extern void func_0202d314(void *archive, int extra);
extern void *func_0202d3e0(void *archive, int recordIndex, int entryIndex);
extern BOOL G2D_GetScreenFromFile_02014dd0(void *file, void **screenOut);
extern BOOL func_02014d38(void *file, void **characterOut);
extern BOOL G2D_GetPaletteFromFile_02014d84(void *file, void **paletteOut);

void GetBgDataFromArchive_0202b554(BgGraphicsData *out, void *archive, int screenIndex, int characterIndex,
                                   int paletteIndex)
{
    void *file;

    func_0202d314(archive, 0);

    out->screen = NULL;
    if (screenIndex >= 0 && (file = func_0202d3e0(archive, 6, screenIndex)) != NULL
        && !G2D_GetScreenFromFile_02014dd0(file, &out->screen)) {
        out->screen = NULL;
    }

    out->character = NULL;
    if (characterIndex >= 0 && (file = func_0202d3e0(archive, 1, characterIndex)) != NULL
        && !func_02014d38(file, &out->character)) {
        out->character = NULL;
    }

    out->palette = NULL;
    if (paletteIndex >= 0 && (file = func_0202d3e0(archive, 0, paletteIndex)) != NULL
        && !G2D_GetPaletteFromFile_02014d84(file, &out->palette)) {
        out->palette = NULL;
    }
}
