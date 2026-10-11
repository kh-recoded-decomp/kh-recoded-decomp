#include "nitro/types.h"

typedef struct BgGraphicsData {
    void *screen;
    void *character;
    void *palette;
} BgGraphicsData;

extern int data_ov039_020bea00;
extern unsigned int BuildSlotImageParams_020bc220(int slot, unsigned int low);
extern u32 func_0202c478(u32 fileId, u32 param2);
extern void GetBgDataFromArchive_0202b554(BgGraphicsData *out, void *archive, int screenIndex, int characterIndex, int paletteIndex);
extern void GXS_LoadBGPltt_020072b4(const void *src, u32 offset, u32 size);
extern void GXS_LoadBG3Char_02007be0(const void *src, u32 offset, u32 size);
extern void *FindActiveRecordById_020b8184(void *pool, u16 id);
extern void TagTracker_InvokeCallback_020b8210(void *tracker, int record);
extern void NNSi_FndFreeFromDefaultHeap_0202a1c4(void *block);

void LoadSubBgAndTriggerTags_020bc488(int slot, unsigned int low, int firstTag, int secondTag, u16 paletteIndex)
{
    void *archive = (void *)func_0202c478(BuildSlotImageParams_020bc220(slot, low), 0xe);
    char *tracker = (char *)data_ov039_020bea00 + 0x144 + 0xc800;
    BgGraphicsData bg;

    GetBgDataFromArchive_0202b554(&bg, archive, -1, 0, paletteIndex);
    GXS_LoadBGPltt_020072b4(*(void **)((char *)bg.palette + 0xc), 0, *(u32 *)((char *)bg.palette + 8));
    GXS_LoadBG3Char_02007be0(*(void **)((char *)bg.character + 0x14), 0, *(u32 *)((char *)bg.character + 0x10));
    if (firstTag >= 0) {
        TagTracker_InvokeCallback_020b8210(tracker, (int)FindActiveRecordById_020b8184(tracker, firstTag));
    }
    if (secondTag >= 0) {
        TagTracker_InvokeCallback_020b8210(tracker, (int)FindActiveRecordById_020b8184(tracker, secondTag));
    }
    NNSi_FndFreeFromDefaultHeap_0202a1c4(archive);
}
