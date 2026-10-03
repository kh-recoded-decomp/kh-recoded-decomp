#include "nitro/types.h"

typedef struct CharacterData {
    u8 pad_00[0x10];
    u32 size;
    void *rawData;
} CharacterData;

typedef struct PaletteData {
    u8 pad_00[0x8];
    u32 size;
    u8 *rawData;
} PaletteData;

typedef struct BgGraphicsData {
    void *screen;
    CharacterData *character;
    PaletteData *palette;
} BgGraphicsData;

typedef struct MenuFlags {
    u8 pad_00[0x4];
    BOOL backgroundLoaded;
} MenuFlags;

extern MenuFlags *data_ov023_020b6f60;

extern void *func_ov027_020ba1d8(void *resource);
extern void *func_ov001_0207123c(void);
extern void func_ov027_020b9d18(void *target, int mode);
extern void GetBgDataFromArchive_0202b554(BgGraphicsData *out, void *archive, int screenIndex, int characterIndex,
                                          int paletteIndex);
extern void *func_ov001_0207b1f4(void);
extern void func_01ff869c(const void *src, void *dest, u32 size);
extern void GXS_LoadBGPltt_020072b4(const void *src, u32 offset, u32 size);
extern void GXS_LoadBG2Char_02007b00(const void *src, u32 offset, u32 size);
extern void func_ov027_020ba1e0(void *resource, int release);
extern void *GetSceneTagTracker_020711b0(void);
extern void *FindActiveRecordById_020b8184(void *pool, int id);
extern void TagTracker_InvokeCallback_020b8210(void *pool, void *record);
extern void func_ov001_02073030(int enable);

void LoadMenuBackground_020b5800(void *resource)
{
    void *archive = func_ov027_020ba1d8(resource);
    BgGraphicsData bg;
    void *tracker;

    func_ov027_020b9d18(func_ov001_0207123c(), 0x19);
    GetBgDataFromArchive_0202b554(&bg, archive, -1, 0, 0);
    {
        u8 *dest = bg.palette->rawData + 0x1c2;
        void *src = func_ov001_0207b1f4();

        func_01ff869c(src, dest, 12);
    }
    GXS_LoadBGPltt_020072b4(bg.palette->rawData, 0, bg.palette->size);
    GXS_LoadBG2Char_02007b00(bg.character->rawData, 0, bg.character->size);
    func_ov027_020ba1e0(resource, 1);
    tracker = GetSceneTagTracker_020711b0();
    TagTracker_InvokeCallback_020b8210(tracker, FindActiveRecordById_020b8184(tracker, 1000));
    TagTracker_InvokeCallback_020b8210(tracker, FindActiveRecordById_020b8184(tracker, 1001));
    data_ov023_020b6f60->backgroundLoaded = TRUE;
    func_ov001_02073030(1);
}
