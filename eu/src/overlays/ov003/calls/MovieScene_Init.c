#include "nitro/types.h"

#define ARCHIVE_FILE_ID(archive, index) ((((u32)(archive) + 0x8000) & 0xfffffc) << 7 | 0x80000000 | (index))

typedef struct MovieBgView {
    void *screen;
    void *character;
    void *palette;
} MovieBgView;

typedef struct MovieInitScene {
    u16 state;
    u16 flags;
    u8 archive[0x648];
    void *streamOwner;
    u8 pad_650[0x1d4];
    u8 font[0xc];
    u8 stream[0x80];
    int field_8b0;
    int streamActive;
    u8 field_8b8;
    u8 field_8b9;
    u8 pad_8ba[6];
    int fadeTarget;
    int skipHeld;
    u8 visiblePlanes;
    u8 pad_8c9[0xb];
    void *bgFile;
    MovieBgView views[27];
} MovieInitScene;

extern MovieInitScene *data_ov003_020658c0;
extern char sOv003_FontEu10allNftr_02065854[];
extern u8 data_ov003_020650f4[];
extern char sOv003_OpOpP2_02065868[];
extern u8 gMovieScriptCommandHandlers[];
extern u8 sOv003_OpScrZ_02065874[];
extern void func_ov003_020643f0(void);
extern char OVERLAY_22_ID[];

extern void *NNSi_FndGetCurrentRootHeap(void);
extern void InitPxiChannelsPair(void);
extern void func_02029f8c(int processor, int overlayId);
extern void func_ov003_02063ae0(void);
extern void MI_CpuFill8(void *dst, int value, int size);
extern int func_0200146c(void *font, char *name);
extern void GX_LoadBGPltt(void *src, u32 offset, u32 size);
extern void GXS_LoadBGPltt(const void *src, u32 offset, u32 size);
extern int GetLanguageIndex(void);
extern int Msg_OpenContainerAndReadHeader(char *path, int heapId, int flags);
extern void *Archive_LoadFile(u32 fileId, u32 heapId);
extern void ZeroHalfThenFree(int handle);
extern void GetBgDataFromArchive(MovieBgView *out, void *archive, int screenIndex, int characterIndex, int paletteIndex);
extern void StoreGlobalArrayEntry(int index, void *value);
extern void func_020257d8(void *archive, u32 size, u32 heapId);
extern int RoundAndInitArchive(void *archive, void *name, int flag, void *extra);
extern void WriteGlobalPackedBits(u32 bitOffset, u32 bitCount, u32 value);

void *MovieScene_Init(int fromTitle)
{
    MovieInitScene *scene;
    int i;
    int handle;
    int localized;
    int index;
    u16 buttons;
    u16 held;

    scene = NNSi_FndGetCurrentRootHeap();
    InitPxiChannelsPair();
    func_02029f8c(0, (int)OVERLAY_22_ID);
    func_ov003_02063ae0();
    data_ov003_020658c0 = scene;
    scene->state = 0;
    scene->flags = 0;
    if (fromTitle == 0) {
        scene->flags |= 0x10;
    }
    scene->fadeTarget = -1;
    localized = 0;
    scene->streamActive = 0;
    scene->field_8b0 = 0;
    scene->field_8b8 = 0;
    scene->visiblePlanes = 0;
    MI_CpuFill8(&scene->streamOwner, 0, 0x1d4);
    func_0200146c(scene->font, sOv003_FontEu10allNftr_02065854);
    GX_LoadBGPltt(data_ov003_020650f4, 0x1a0, 0x20);
    GXS_LoadBGPltt(data_ov003_020650f4, 0x1a0, 0x20);
    scene->streamOwner = scene->stream;
    if (GetLanguageIndex() != 0) {
        localized = 1;
    }
    handle = Msg_OpenContainerAndReadHeader(sOv003_OpOpP2_02065868, 0xe, 0);
    scene->bgFile = Archive_LoadFile(ARCHIVE_FILE_ID(handle, localized & 0x1ff), 0xe);
    ZeroHalfThenFree(handle);
    for (i = 0; i < 14; i++) {
        index = i * 2;
        GetBgDataFromArchive(&scene->views[index], scene->bgFile, index, index, i);
        if (i < 13) {
            index++;
            GetBgDataFromArchive(&scene->views[index], scene->bgFile, index, index, -1);
        }
    }
    StoreGlobalArrayEntry(3, gMovieScriptCommandHandlers);
    func_020257d8(scene->archive, 0x2000, 0x11);
    RoundAndInitArchive(scene->archive, sOv003_OpScrZ_02065874, 0, &scene->streamOwner);
    scene->flags |= 1;
    scene->field_8b9 = 0;
    buttons = ((*(vu16 *)0x04000130 | *(vu16 *)0x02ffffa8) ^ 0x2fff) & 0x2fff;
    held = buttons & ~((buttons & 0x40) << 1) & ~((buttons & 0x20) >> 1);
    scene->skipHeld = held & 8;
    WriteGlobalPackedBits(0x1a02, 3, GetLanguageIndex());
    return func_ov003_020643f0;
}
