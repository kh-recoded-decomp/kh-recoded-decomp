#include "nitro/types.h"

typedef struct {
    u8 pad_00[8];
    u32 size;
    void *data;
} PaletteBlock;

typedef struct {
    u8 pad_00[0x10];
    u32 size;
    void *data;
} CharacterBlock;

typedef struct {
    void *screen;
    CharacterBlock *character;
    PaletteBlock *palette;
} BgGraphicsData;

typedef struct {
    u32 words[5];
} TagTrackerConfig;

extern const TagTrackerConfig data_ov086_020c21bc;
extern u32 BuildSlotImageParams_020bc220(int slot, u32 low);
extern void *func_0202c48c(u32 fileId, u32 heapId);
extern void GetBgDataFromArchive_0202b554(BgGraphicsData *out, void *archive, int screenIndex, int characterIndex, int paletteIndex);
extern void GXS_LoadBGPltt_020072b4(const void *src, u32 offset, u32 size);
extern void GXS_LoadBG3Char_02007be0(const void *src, u32 offset, u32 size);
extern void NNSi_FndFreeFromDefaultHeap_0202a1c4(void *block);
extern int func_02014d38(void *file, CharacterBlock **character);
extern void func_020033e0(void);
extern void func_ov027_020b7d58(void *tracker, TagTrackerConfig *config);
extern void func_ov027_020b7e24(void *tracker, u32 imageParams);
extern void *FindActiveRecordById_020b8184(void *pool, u32 recordId);
extern void TagTracker_InvokeCallback_020b8210(void *pool, void *record);

void LoadRecordSubScreenGraphics_020c0f08(u8 *menu)
{
    BgGraphicsData bg;
    TagTrackerConfig config = data_ov086_020c21bc;
    CharacterBlock *character;
    void *file;

    file = func_0202c48c(BuildSlotImageParams_020bc220(2, 0x16), 0xe);
    GetBgDataFromArchive_0202b554(&bg, file, -1, 0, 0);
    GXS_LoadBGPltt_020072b4(bg.palette->data, 0, bg.palette->size);
    GXS_LoadBG3Char_02007be0(bg.character->data, 0, bg.character->size);
    NNSi_FndFreeFromDefaultHeap_0202a1c4(file);
    file = func_0202c48c(BuildSlotImageParams_020bc220(3, 2), 0xe);
    func_02014d38(file, &character);
    func_020033e0();
    GXS_LoadBG3Char_02007be0(character->data, 0, character->size);
    NNSi_FndFreeFromDefaultHeap_0202a1c4(file);
    func_ov027_020b7d58(menu + 0x190, &config);
    func_ov027_020b7e24(menu + 0x190, BuildSlotImageParams_020bc220(2, 0x10));
    TagTracker_InvokeCallback_020b8210(menu + 0x190, FindActiveRecordById_020b8184(menu + 0x190, 0x3e8));
}
