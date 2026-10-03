#include "nitro/types.h"

typedef struct MovieArchiveInfo {
    void *buffer;
    u8 pad_04[0x54];
    s32 resourceBase;
    u8 pad_5C[0x178];
} MovieArchiveInfo;

typedef struct MovieState {
    u16 unk_00;
    u16 flags;
    u8 loader[0x648];
    MovieArchiveInfo archiveInfo;
    u8 pad_820[0x4];
    u8 font[0xc];
    u8 pxi[0x80];
    s32 unk_8B0;
    u8 unk_8B4;
    u8 unk_8B5;
    u8 pad_8B6[0x2];
    s32 unk_8B8;
    s32 unk_8BC;
    u8 text[0x100];
    u8 pad_9C0[0x100];
    s32 unk_AC0;
    s32 unk_AC4;
    s32 unk_AC8;
    s32 unk_ACC;
    s32 mode;
} MovieState;

typedef struct MovieParams {
    u8 pad_00[0x8];
    void *resourceDir;
    s32 useMainScreen;
    char name[0x80];
    s32 mode;
} MovieParams;

typedef struct MovieStateGlobals {
    MovieState *state;
    s32 unk_04;
} MovieStateGlobals;

extern MovieStateGlobals data_ov022_020b7d80;
extern u8 data_ov022_020b7ccc[];
extern u8 data_ov022_020b7c8c[];
extern u8 data_ov022_020b7ce0[];

extern MovieState *NNSi_FndGetCurrentRootHeap_0202a764(void);
extern void func_02028bf4(void);
extern void func_01ff8830(void *dest, int value, int size);
extern void func_ov022_020a7798(void);
extern void func_020257c4(void *loader, int size, int count);
extern void func_02001458(void *font, void *data);
extern void func_02007250(void *src, int offset, int size);
extern void GXS_LoadBGPltt_020072b4(void *src, int offset, int size);
extern void StoreGlobalArrayEntry_02025668(s32 index, s32 value);
extern void FormatSessionNumber_02063578(int number, char *out);
extern s32 func_ov001_020636e4(void);
extern u32 findSharedResourceByName_0202cd8c(s32 dir, const char *name);
extern u32 Strlen_02021e44(const char *str);
extern u32 func_0202255c(const char *str);
extern void RoundAndInitArchive_020258b0(void *loader, u32 archiveId, const char *name, MovieArchiveInfo *info);
extern void SetLoaderCallbacks_02025914(void *loader, int writeHandler, int readHandler);
extern void func_ov001_0206459c(void);
extern void func_ov001_02064574(void);
extern void func_ov022_020a7414(void);

void *StartMoviePlaybackState_020a7000(MovieParams *params)
{
    MovieState *state = NNSi_FndGetCurrentRootHeap_0202a764();
    s32 resourceDir;
    u32 archiveId;
    const char *name;
    char fileName[0x80];
    s32 base;
    u32 index;

    func_02028bf4();
    data_ov022_020b7d80.state = state;
    state->unk_00 = 0;
    state->flags = 0;
    state->unk_8B8 = -1;
    state->unk_8B0 = 0;
    state->unk_8B4 = 0;
    state->unk_8BC = 0;
    state->mode = params->mode;
    func_01ff8830(state->text, 0, 0x100);
    func_01ff8830(&state->archiveInfo, 0, sizeof(MovieArchiveInfo));
    func_ov022_020a7798();
    func_020257c4(state->loader, 0x8000, 0xd);
    func_02001458(state->font, data_ov022_020b7ccc);
    func_02007250(data_ov022_020b7c8c, 0x1a0, 0x40);
    GXS_LoadBGPltt_020072b4(data_ov022_020b7c8c, 0x1a0, 0x40);
    state->archiveInfo.buffer = state->pxi;
    StoreGlobalArrayEntry_02025668(3, (s32)data_ov022_020b7ce0);

    resourceDir = (s32)params->resourceDir;
    if (resourceDir == 0) {

        FormatSessionNumber_02063578(0, fileName);
        state->archiveInfo.resourceBase = func_ov001_020636e4();
        base = func_ov001_020636e4();
        index = findSharedResourceByName_0202cd8c(func_ov001_020636e4(), fileName);
        archiveId = ((base + 0x8000) & 0xfffffc) << 7 | 0x80000000 | (index & 0x1ff);
        name = params->name;
    } else {
        if (Strlen_02021e44(params->name) > 2) {
            index = findSharedResourceByName_0202cd8c(resourceDir, params->name);
        } else {
            index = func_0202255c(params->name);
        }
        archiveId = (((s32)params->resourceDir + 0x8000) & 0xfffffc) << 7 | 0x80000000 | (index & 0x1ff);
        name = NULL;
    }
    RoundAndInitArchive_020258b0(state->loader, archiveId, name, &state->archiveInfo);
    SetLoaderCallbacks_02025914(state->loader, (int)func_ov001_0206459c, (int)func_ov001_02064574);
    switch (state->mode) {
    case 3:
        SetLoaderCallbacks_02025914(state->loader, 0, 0);
        break;
    case 1:
    case 2:
        SetLoaderCallbacks_02025914(state->loader, 0, 0);
        break;
    }
    if (params->useMainScreen != 0) {
        state->flags |= 8;
    }
    state->flags |= 1;
    state->unk_8B5 = 0;
    state->unk_AC0 = 0;
    state->unk_AC4 = 0;
    state->unk_AC8 = 0;
    state->unk_ACC = 0;
    data_ov022_020b7d80.unk_04 = 0;
    return func_ov022_020a7414;
}
