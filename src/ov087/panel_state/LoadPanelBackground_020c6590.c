#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x10];
    u32 size;
    void *rawData;
} CharacterData;

typedef struct {
    u8 pad_00[8];
    u32 size;
    void *rawData;
} PaletteData;

typedef struct {
    void *screen;
    CharacterData *character;
    PaletteData *palette;
} BgGraphicsData;

extern void *func_ov039_020bc18c(void);
extern u32 BuildSlotImageParams_020bc220(int slot, u32 low);
extern void *func_0202c48c(u32 fileId, int heapId);
extern void GetBgDataFromArchive_0202b554(BgGraphicsData *out, void *archive, int screenIndex, int characterIndex,
                                          int paletteIndex);
extern void func_02007250(const void *src, u32 offset, u32 size);
extern void GX_LoadBG3Char_02007b70(const void *src, u32 offset, u32 size);
extern void NNSi_FndFreeFromDefaultHeap_0202a1c4(void *block);
extern void func_ov027_020b7e24(void *pool, u32 params);
extern void *FindActiveRecordById_020b8184(void *pool, u32 recordId);
extern void TagTracker_InvokeCallback_020b8210(void *pool, void *record);

void LoadPanelBackground_020c6590(void)
{
    void *pool = func_ov039_020bc18c();
    void *archive = func_0202c48c(BuildSlotImageParams_020bc220(3, 1), 0xe);
    BgGraphicsData bg;

    GetBgDataFromArchive_0202b554(&bg, archive, -1, 0, 0);
    func_02007250(bg.palette->rawData, 0, bg.palette->size);
    GX_LoadBG3Char_02007b70(bg.character->rawData, 0, bg.character->size);
    NNSi_FndFreeFromDefaultHeap_0202a1c4(archive);
    func_ov027_020b7e24(pool, BuildSlotImageParams_020bc220(2, 0x11));
    TagTracker_InvokeCallback_020b8210(pool, FindActiveRecordById_020b8184(pool, 0));
}
