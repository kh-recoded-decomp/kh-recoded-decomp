#include "nitro/types.h"

#pragma opt_propagation off

#define ARCHIVE_FILE_ID(archive, index) ((((archive) + 0x8000U) & 0xfffffc) << 7 | 0x80000000 | (index))

typedef struct {
    void *screen;
    void *character;
    void *palette;
} BgGraphicsData;

typedef struct {
    void *archive;
    BgGraphicsData bg;
} BgResource;

typedef struct {
    u8 pad_00[0x10];
    int size;
} CharData;

typedef struct {
    u32 mainArchive;
    u32 subArchive;
    u8 pad_008[0x1b0 - 8];
    BgResource frameBg;
    BgResource panelBg;
    BgResource mainBg;
    BgResource subBg;
    BgResource glyphBg;
} SceneWork;

extern void *Archive_LoadFile(u32 fileId, int heapId);
extern void GetBgDataFromArchive(BgGraphicsData *out, void *archive, int screenIndex, int characterIndex, int paletteIndex);
extern void DispatchByPartType(int layer, void *screen, void *character, void *palette, int value, int flags);
extern int Gfx_EnqueueTableCmdAt14(int index, void *data, int offset, int size);

static inline void LoadBgResource(BgResource *resource, u32 archive, int index)
{
    void *file = Archive_LoadFile(ARCHIVE_FILE_ID(archive, index), 0xe);

    resource->archive = file;
    GetBgDataFromArchive(&resource->bg, resource->archive, 0, 0, 0);
}

void LoadSceneBackgrounds(SceneWork *work)
{
    LoadBgResource(&work->mainBg, work->mainArchive, 5);
    DispatchByPartType(0, work->mainBg.bg.screen, work->mainBg.bg.character, work->mainBg.bg.palette, 0x1e, 4);
    LoadBgResource(&work->panelBg, work->mainArchive, 4);
    LoadBgResource(&work->frameBg, work->mainArchive, 3);
    DispatchByPartType(2, work->frameBg.bg.screen, work->frameBg.bg.character, work->frameBg.bg.palette, 0x1d, 0);
    LoadBgResource(&work->glyphBg, work->subArchive, 0);
    Gfx_EnqueueTableCmdAt14(2, work->glyphBg.bg.character, 0, ((CharData *)work->glyphBg.bg.character)->size);
    LoadBgResource(&work->subBg, work->mainArchive, 0);
    DispatchByPartType(4, work->subBg.bg.screen, work->subBg.bg.character, work->subBg.bg.palette, 0x1f, 0);
}
