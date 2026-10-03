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
extern char data_ov003_02065854[];
extern u8 data_ov003_020650f4[];
extern char data_ov003_02065868[];
extern u8 data_ov003_02065880[];
extern u8 data_ov003_02065874[];
extern void func_ov003_020643f0(void);
extern char OverlayId22_00000016[];

extern void *NNSi_FndGetCurrentRootHeap_0202a764(void);
extern void func_02028bf4(void);
extern void func_02029f78(int processor, int overlayId);
extern void MoviePlayer_SetupDisplay_02063ae0(void);
extern void func_01ff8830(void *dst, int value, int size);
extern int func_02001458(void *font, char *name);
extern void func_02007250(void *src, u32 offset, u32 size);
extern void GXS_LoadBGPltt_020072b4(const void *src, u32 offset, u32 size);
extern int func_0202b788(void);
extern int Msg_OpenContainerAndReadHeader_0202cc6c(char *path, int heapId, int flags);
extern void *func_0202c478(u32 fileId, u32 heapId);
extern void ZeroHalfThenFree_0202cd78(int handle);
extern void GetBgDataFromArchive_0202b554(MovieBgView *out, void *archive, int screenIndex, int characterIndex, int paletteIndex);
extern void StoreGlobalArrayEntry_02025668(int index, void *value);
extern void func_020257c4(void *archive, u32 size, u32 heapId);
extern int RoundAndInitArchive_020258b0(void *archive, void *name, int flag, void *extra);
extern void WriteGlobalPackedBits_02027360(u32 bitOffset, u32 bitCount, u32 value);

void *MovieScene_Init_02063bb0(int fromTitle)
{
    MovieInitScene *scene;
    int i;
    int handle;
    int localized;
    int index;
    u16 buttons;
    u16 held;

    scene = NNSi_FndGetCurrentRootHeap_0202a764();
    func_02028bf4();
    func_02029f78(0, (int)OverlayId22_00000016);
    MoviePlayer_SetupDisplay_02063ae0();
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
    func_01ff8830(&scene->streamOwner, 0, 0x1d4);
    func_02001458(scene->font, data_ov003_02065854);
    func_02007250(data_ov003_020650f4, 0x1a0, 0x20);
    GXS_LoadBGPltt_020072b4(data_ov003_020650f4, 0x1a0, 0x20);
    scene->streamOwner = scene->stream;
    if (func_0202b788() != 0) {
        localized = 1;
    }
    handle = Msg_OpenContainerAndReadHeader_0202cc6c(data_ov003_02065868, 0xe, 0);
    scene->bgFile = func_0202c478(ARCHIVE_FILE_ID(handle, localized & 0x1ff), 0xe);
    ZeroHalfThenFree_0202cd78(handle);
    for (i = 0; i < 14; i++) {
        index = i * 2;
        GetBgDataFromArchive_0202b554(&scene->views[index], scene->bgFile, index, index, i);
        if (i < 13) {
            index++;
            GetBgDataFromArchive_0202b554(&scene->views[index], scene->bgFile, index, index, -1);
        }
    }
    StoreGlobalArrayEntry_02025668(3, data_ov003_02065880);
    func_020257c4(scene->archive, 0x2000, 0x11);
    RoundAndInitArchive_020258b0(scene->archive, data_ov003_02065874, 0, &scene->streamOwner);
    scene->flags |= 1;
    scene->field_8b9 = 0;
    buttons = ((*(vu16 *)0x04000130 | *(vu16 *)0x02ffffa8) ^ 0x2fff) & 0x2fff;
    held = buttons & ~((buttons & 0x40) << 1) & ~((buttons & 0x20) >> 1);
    scene->skipHeld = held & 8;
    WriteGlobalPackedBits_02027360(0x1a02, 3, func_0202b788());
    return func_ov003_020643f0;
}
