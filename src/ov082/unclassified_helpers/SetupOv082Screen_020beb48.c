#include "nitro/types.h"

#define ARCHIVE_FILE_ID(handle, index) ((((u32)(handle) + 0x8000) & 0xfffffc) << 7 | 0x80000000 | (index))

typedef struct ScreenData {
    u8 pad_00[0x8];
    u32 size;
    u8 rawData[1];
} ScreenData;

typedef struct CharacterData {
    u8 pad_00[0x10];
    u32 size;
    void *rawData;
} CharacterData;

typedef struct PaletteData {
    u8 pad_00[0x8];
    u32 size;
    void *rawData;
} PaletteData;

typedef struct BgGraphicsData {
    ScreenData *screen;
    CharacterData *character;
    PaletteData *palette;
} BgGraphicsData;

typedef struct WindowStyle {
    u16 unk_00[4];
    u16 fillColor;
    u16 unk_0A[3];
} WindowStyle;

typedef struct TextWindow {
    u8 data[0x34];
} TextWindow;

typedef struct Ov081State {
    u32 archive;
    u32 subArchive;
} Ov081State;

typedef struct Ov082State {
    u8 list[0x28];
    u8 pad_0028[0xd4 - 0x28];
    u8 rowTiles[9][0x600];
    TextWindow window;
    int needsRedraw;
    void *entryFile;
    void *headerFile;
    BgGraphicsData entryBg;
    BgGraphicsData headerBg;
} Ov082State;

extern void *data_0205fe0c;
extern const WindowStyle data_020bf654;

extern Ov081State *func_ov081_020c5bd8(void);
extern void func_0200672c(int value);
extern void G2x_SetBlendAlpha_02006850(vu32 *reg, int plane1, int plane2, int ev1, int ev2);
extern void *G2S_GetBG1ScrPtr_02006e68(void);
extern void *G2S_GetBG2ScrPtr_02006f0c(void);
extern void *G2S_GetBG3ScrPtr_02007004(void);
extern void func_01ff8740(u32 value, void *dst, u32 size);
extern void *func_0202c48c(u32 fileId, int heapId);
extern void GetBgDataFromArchive_0202b554(BgGraphicsData *out, void *archive, int screenIndex, int characterIndex,
                                          int paletteIndex);
extern void GXS_LoadBGPltt_020072b4(const void *src, u32 offset, u32 size);
extern void GXS_LoadBG2Char_02007b00(const void *src, u32 offset, u32 size);
extern void GXS_LoadBG3Scr_02007860(const void *src, u32 offset, u32 size);
extern void NNSi_FndFreeFromDefaultHeap_0202a1c4(void *block);
extern void DrawEntryRowFrames_020bf260(Ov082State *state);
extern void OpenTextFrame_020be5b8(int position, int size, int palette, TextWindow *window, WindowStyle *style);
extern u16 *func_ov039_020bcb20(void *save);
extern void SetTextColorIfFits_020bcd04(TextWindow *window, int messageId, u16 *text);
extern void DrawTextAnchored_020015a0(TextWindow *window, int x, int y, int color, u32 flags, const u16 *text);
extern void Text_UploadTileBuffer_02001520(TextWindow *window);
extern void StepEntryListCursor_020bf448(Ov082State *state);
extern void RefreshEntryRows_020bef08(Ov082State *state);

static inline void SetWindowOutsidePlane(int planeMask, BOOL effect)
{
    u32 value = (*(vu16 *)0x0400104a & ~0x3f) | planeMask;
    if (effect) {
        value |= 0x20;
    }
    *(vu16 *)0x0400104a = (u16)value;
}

static inline void SetWindow0InsidePlane(int planeMask, BOOL effect)
{
    u32 value = (*(vu16 *)0x04001048 & ~0x3f) | planeMask;
    if (effect) {
        value |= 0x20;
    }
    *(vu16 *)0x04001048 = (u16)value;
}

static inline void SetWindow1InsidePlane(int planeMask, BOOL effect)
{
    u32 value = (*(vu16 *)0x04001048 & ~0x3f00) | (planeMask << 8);
    if (effect) {
        value |= 0x2000;
    }
    *(vu16 *)0x04001048 = (u16)value;
}

void SetupOv082Screen_020beb48(Ov082State *state)
{
    Ov081State *source = func_ov081_020c5bd8();
    BgGraphicsData bg;
    WindowStyle style;
    void *archive;
    u16 *title;

    func_0200672c(0);
    G2x_SetBlendAlpha_02006850((vu32 *)0x04001050, 1, 0x1e, 16, 16);
    *(vu32 *)0x04001000 = (*(vu32 *)0x04001000 & ~0x1f00) | 0x1f00;
    *(vu16 *)0x04001008 = (u16)((*(vu16 *)0x04001008 & ~3) | 0);
    *(vu16 *)0x0400100a = (u16)((*(vu16 *)0x0400100a & ~3) | 1);
    *(vu16 *)0x0400100c = (u16)((*(vu16 *)0x0400100c & ~3) | 2);
    *(vu16 *)0x0400100e = (u16)((*(vu16 *)0x0400100e & ~3) | 3);
    *(vu32 *)0x04001010 = 0;
    *(vu32 *)0x04001014 = 0x1fe0000;
    *(vu32 *)0x04001018 = 0;
    *(vu32 *)0x0400101c = 0;
    SetWindowOutsidePlane(0x1f, TRUE);
    SetWindow0InsidePlane(0x1f, TRUE);
    SetWindow1InsidePlane(0x1f, TRUE);
    *(vu32 *)0x04001000 = (*(vu32 *)0x04001000 & ~0xe000) | 0x6000;
    *(vu16 *)0x04001008 = (u16)((*(vu16 *)0x04001008 & 0x43) | 0xa00);
    *(vu16 *)0x0400100a = (u16)((*(vu16 *)0x0400100a & 0x43) | 0xb00);
    *(vu16 *)0x0400100c = (u16)((*(vu16 *)0x0400100c & 0x43) | 0xd00);
    *(vu16 *)0x0400100e = (u16)((*(vu16 *)0x0400100e & 0x43) | 0xf00);

    func_01ff8740(0, G2S_GetBG1ScrPtr_02006e68(), 0x600);
    func_01ff8740(0, G2S_GetBG2ScrPtr_02006f0c(), 0x600);
    func_01ff8740(0, G2S_GetBG3ScrPtr_02007004(), 0x600);

    state->entryFile = func_0202c48c(ARCHIVE_FILE_ID(source->archive, 1), 0xf);
    state->headerFile = func_0202c48c(ARCHIVE_FILE_ID(source->archive, 1), 0xf);
    GetBgDataFromArchive_0202b554(&state->entryBg, state->entryFile, 1, 0, 0);
    GetBgDataFromArchive_0202b554(&state->headerBg, state->headerFile, 2, 0, 0);
    GXS_LoadBGPltt_020072b4(state->entryBg.palette->rawData, 0, state->entryBg.palette->size);
    GXS_LoadBG2Char_02007b00(state->entryBg.character->rawData, 0, state->entryBg.character->size);
    DrawEntryRowFrames_020bf260(state);

    archive = func_0202c48c(ARCHIVE_FILE_ID(source->archive, 1), 0xf);
    GetBgDataFromArchive_0202b554(&bg, archive, 0, 0, 0);
    GXS_LoadBG3Scr_02007860(bg.screen->rawData, 0, bg.screen->size);
    NNSi_FndFreeFromDefaultHeap_0202a1c4(archive);

    archive = func_0202c48c(ARCHIVE_FILE_ID(source->subArchive, 1), 0xf);
    GetBgDataFromArchive_0202b554(&bg, archive, 0, 0, 0);
    GXS_LoadBG2Char_02007b00(bg.character->rawData, 0x1000, bg.character->size);
    NNSi_FndFreeFromDefaultHeap_0202a1c4(archive);

    func_01ff8740(0, state->rowTiles, sizeof(state->rowTiles));
    style = data_020bf654;
    OpenTextFrame_020be5b8(8, 0x20018, 4, &state->window, &style);
    title = func_ov039_020bcb20(data_0205fe0c);
    SetTextColorIfFits_020bcd04(&state->window, 0xac, title);
    DrawTextAnchored_020015a0(&state->window, 0xbe, 2, 2, 0x20, title);
    Text_UploadTileBuffer_02001520(&state->window);
    StepEntryListCursor_020bf448(state);
    RefreshEntryRows_020bef08(state);
}
