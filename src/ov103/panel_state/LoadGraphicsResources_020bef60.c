#include "nitro/types.h"
#include "nnsys/g2d.h"

#define ARCHIVE_FILE_ID(archive, index) ((((u32)(archive) + 0x8000) & 0xfffffc) << 7 | 0x80000000 | (index))

typedef struct {
    NNSG2dScreenData *screen;
    NNSG2dCharacterData *character;
    NNSG2dPaletteData *palette;
} GraphicsView;

typedef struct {
    void *fileData;
    GraphicsView view;
} GraphicsResource;

typedef struct {
    u8 pad_000[0x10];
    u16 *archiveFiles[2];
    u8 pad_018[0x134 - 0x18];
    GraphicsResource resources[4];
} MenuScene;

extern void *func_0202c478(u32 fileId, u32 heapId);
extern void func_0202b554(GraphicsView *view, void *file, int screenIndex, int characterIndex, int paletteIndex);
extern void DispatchByPartType_0202b4c0(int bgIndex, NNSG2dScreenData *screen, NNSG2dCharacterData *character,
                                        NNSG2dPaletteData *palette, int mask, int flags);
extern int Gfx_EnqueueTableCmdAt14_0202b448(int bgIndex, NNSG2dCharacterData *character, u32 offset, u32 size);

void LoadGraphicsResources_020bef60(MenuScene *scene)
{
    GraphicsResource *resource;

    resource = &scene->resources[0];
    resource->fileData = func_0202c478(ARCHIVE_FILE_ID(scene->archiveFiles[0], 0xc), 0xe);
    func_0202b554(&resource->view, resource->fileData, 0, 0, 0);
    DispatchByPartType_0202b4c0(0, resource->view.screen, resource->view.character, resource->view.palette, 0x1f, 0);

    resource = &scene->resources[1];
    resource->fileData = func_0202c478(ARCHIVE_FILE_ID(scene->archiveFiles[1], 0), 0xe);
    func_0202b554(&resource->view, resource->fileData, 0, 0, 0);
    Gfx_EnqueueTableCmdAt14_0202b448(0, resource->view.character, 0, resource->view.character->szByte);

    resource = &scene->resources[2];
    resource->fileData = func_0202c478(ARCHIVE_FILE_ID(scene->archiveFiles[0], 0xb), 0xe);
    func_0202b554(&resource->view, resource->fileData, 0, 0, 0);
    DispatchByPartType_0202b4c0(6, resource->view.screen, resource->view.character, resource->view.palette, 0x1f, 0);
}
