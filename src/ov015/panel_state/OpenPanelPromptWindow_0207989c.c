#include "nitro/types.h"

typedef struct BgGraphicsData {
    void *screen;
    void *character;
    void *palette;
} BgGraphicsData;

typedef struct PanelWork {
    u8 pad_0000[0x65f4];
    void *tileObject;
} PanelWork;

extern char data_ov015_0207e8ac[];
extern PanelWork *data_ov015_020812e0;

extern int Msg_OpenContainerAndReadHeader_0202cc6c(const char *name, u32 mode, BOOL allocFromEnd);
extern void *func_0202c48c(u32 fileId, u32 type);
extern void GetBgDataFromArchive_0202b554(BgGraphicsData *out, void *archive, int screenIndex, int characterIndex,
                                          int paletteIndex);
extern void *G2S_GetBG2ScrPtr_02006f0c(void);
extern void *G2S_GetBG2CharPtr_02007170(void);
extern void CopyClippedScreenRegion_020167d0(void *dst, void *screen, int srcX, int srcY, int dstX, int dstY,
                                             int dstW, int dstH, int width, int height);
extern void func_ov015_02079cd4(void **slot);
extern u32 func_ov002_02061948(void);
extern void *CreateTileObject_02079c54(u32 ownerId, u32 value, u16 *layout, void *tileData, void *mapData);
extern void func_ov015_020789b8(void *object, int a, int b, int c, int d, int e);
extern void Text_UploadTileBuffer_02001520(void *surface);
extern void NNSi_FndFreeFromDefaultHeap_0202a1c4(void *block);
extern void ZeroHalfThenFree_0202cd78(int handle);
extern BOOL PlaySoundEffect_0204d924(int seqArcNo, int index);

void OpenPanelPromptWindow_0207989c(int x, int y, int style)
{
    BgGraphicsData bgData;
    u16 layout[8];
    int handle;
    void *archive;
    u32 slot;
    void *charPtr;

    handle = Msg_OpenContainerAndReadHeader_0202cc6c(data_ov015_0207e8ac, 0x10, 0);
    archive = func_0202c48c(((handle + 0x8000U) & 0xfffffc) << 7 | 0x80000001, 0x10);
    GetBgDataFromArchive_0202b554(&bgData, archive, 1, -1, -1);
    CopyClippedScreenRegion_020167d0(G2S_GetBG2ScrPtr_02006f0c(), bgData.screen, 0, 0, x, y, 0x20, 0x20, 0x1c, 5);
    layout[0] = x + 1;
    layout[1] = y + 1;
    layout[2] = 0x1a;
    layout[3] = 3;
    layout[4] = 0x32d;
    layout[5] = 0;
    layout[6] = 0;
    layout[7] = 2;
    func_ov015_02079cd4(&data_ov015_020812e0->tileObject);
    slot = func_ov002_02061948();
    charPtr = G2S_GetBG2CharPtr_02007170();
    data_ov015_020812e0->tileObject = CreateTileObject_02079c54(6, slot, layout, charPtr, G2S_GetBG2ScrPtr_02006f0c());
    func_ov015_020789b8(data_ov015_020812e0->tileObject, -1, -1, 0xf, 0, style);
    Text_UploadTileBuffer_02001520(data_ov015_020812e0->tileObject);
    if (archive != NULL) {
        NNSi_FndFreeFromDefaultHeap_0202a1c4(archive);
    }
    ZeroHalfThenFree_0202cd78(handle);
    PlaySoundEffect_0204d924(2, 0xb);
}
