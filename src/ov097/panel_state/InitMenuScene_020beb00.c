#include "nitro/types.h"

typedef struct {
    void *buffer;
    u8 pad_04[8];
} GlyphBuffer;

typedef struct {
    u16 *lines[0x3e8 / 4];
    int lineCount;
    int popupRows[(0x414 - 0x3ec) / 4];
} EntryLayout;

typedef struct {
    int handle;
    int visibleRows;
    int totalRows;
    int slots[8];
} ScrollListDesc;

typedef struct {
    char text[9];
} PopupTag;

typedef struct {
    int selectedEntry;
    BOOL unk_04;
    u8 pad_0008[0xcde4 - 0x8];
    GlyphBuffer glyphBuffers[3];
    EntryLayout layouts[8];
    u8 pad_eea8[0xf06c - 0xeea8];
    int unk_f06c;
    int unk_f070;
    int unk_f074;
    int unk_f078;
    int unk_f07c;
    int unk_f080;
    u8 pad_f084[0xf0cc - 0xf084];
    int entryCount;
} MenuScene;

extern MenuScene *g_menuScene_020c2520;
extern PopupTag data_ov097_020c1dac;
extern ScrollListDesc data_ov097_020c1ec4;
extern ScrollListDesc data_ov097_020c1ef0;
extern void SetStateFlagBits_020bc688(u8 clearMask, u8 setBits);
extern void MIi_CpuClearFast_01ff8740(u32 data, void *dest, u32 size);
extern void MIi_CpuCopy8_01ff878c(const void *src, void *dest, u32 size);
extern void SyncUnlockedEntryFlags_020c14c0(MenuScene *scene);
extern void SetupMenuDisplay_020bf44c(MenuScene *scene);
extern void func_ov097_020bf6a8(MenuScene *scene);
extern void LoadMenuGraphics_020bf714(MenuScene *scene);
extern void InitMenuTextLayers_020bf93c(MenuScene *scene);
extern void InitMenuPanels_020bfdcc(MenuScene *scene);
extern void ApplyTouchRegionBounds_020c0e5c(MenuScene *scene);
extern void ResetScrollTrack_020c1228(int trackIndex);
extern void *func_ov027_020ba2a8(GlyphBuffer *view, int index);
extern int compareByteStrings_02021c54(void *leftBytes, void *rightBytes, int length);
extern void CreateEntryPopups_020c0bc0(MenuScene *scene);
extern void SetupScrollList_020c02f4(ScrollListDesc *desc, MenuScene *scene);
extern void RefreshListPanels_020bfb38(int listIndex, MenuScene *scene);
extern void func_ov097_020c1558(int value, MenuScene *scene);

BOOL InitMenuScene_020beb00(MenuScene *scene)
{
    PopupTag tag;
    ScrollListDesc desc;
    int i;
    u16 *text;
    GlyphBuffer *descriptions;
    EntryLayout *layout;
    int popupCount;

    g_menuScene_020c2520 = scene;
    SetStateFlagBits_020bc688(5, 0);
    MIi_CpuClearFast_01ff8740(0, scene, 0xf0d0);
    scene->selectedEntry = 0;
    scene->unk_04 = 0;
    scene->unk_f078 = 0;
    scene->unk_f07c = 0;
    scene->unk_f080 = 0;
    scene->entryCount = 1;
    scene->unk_f06c = 0;
    scene->unk_f074 = 0;
    scene->unk_f070 = 0;
    SyncUnlockedEntryFlags_020c14c0(scene);
    SetupMenuDisplay_020bf44c(scene);
    func_ov097_020bf6a8(scene);
    LoadMenuGraphics_020bf714(scene);
    InitMenuTextLayers_020bf93c(scene);
    InitMenuPanels_020bfdcc(scene);
    ApplyTouchRegionBounds_020c0e5c(scene);
    ResetScrollTrack_020c1228(0);
    descriptions = &scene->glyphBuffers[2];
    tag = data_ov097_020c1dac;
    for (i = 0; i < 8; i++) {
        layout = &scene->layouts[i];
        popupCount = 0;
        text = func_ov027_020ba2a8(descriptions, i);
        layout->lineCount = 0;
        layout->lines[layout->lineCount] = text;
        while (*text != 0) {
            if (*text == '\n') {
                *text++ = 0;
                layout->lineCount++;
                layout->lines[layout->lineCount] = text;
            } else if (compareByteStrings_02021c54(text, &tag, 8) == 0) {
                layout->popupRows[popupCount] = layout->lineCount * 16 + 0x58;
                text[3] = 0;
                layout->lines[layout->lineCount] = text + 3;
                popupCount++;
                layout->lineCount++;
                layout->lines[layout->lineCount] = text + 3;
                layout->lineCount++;
                layout->lines[layout->lineCount] = text + 3;
                layout->lineCount++;
                layout->lines[layout->lineCount] = text + 3;
                layout->lineCount++;
                layout->lines[layout->lineCount] = text + 3;
                layout->lineCount++;
                layout->lines[layout->lineCount] = text + 3;
                layout->lineCount++;
                layout->lines[layout->lineCount] = text + 3;
                text += 4;
            } else {
                text++;
            }
        }
        layout->lineCount++;
    }
    CreateEntryPopups_020c0bc0(scene);
    MIi_CpuCopy8_01ff878c(&data_ov097_020c1ec4, &desc, sizeof(desc));
    desc.visibleRows = desc.totalRows = scene->entryCount;
    SetupScrollList_020c02f4(&desc, scene);
    data_ov097_020c1ef0.totalRows = scene->layouts[scene->selectedEntry].lineCount;
    SetupScrollList_020c02f4(&data_ov097_020c1ef0, scene);
    RefreshListPanels_020bfb38(-1, scene);
    func_ov097_020c1558(1, scene);
    return TRUE;
}
