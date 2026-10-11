#include "nitro/types.h"

#define REG_DB_DISPCNT (*(vu32 *)0x04001000)

typedef struct {
    void *screen;
    void *character;
    void *palette;
} GraphicsView;

typedef struct {
    void *fileData;
    GraphicsView view;
} GraphicsResource;

typedef struct {
    int entryIndex;
    u8 pad_004[0xc];
    u32 archiveBase;
    u8 pad_014[0x164 - 0x14];
    GraphicsResource background;
} MenuScene;

extern u32 data_ov103_020c04b4[];
extern void NNSi_FndFreeFromDefaultHeap_0202a1c4(void *block);
extern void *G2S_GetBG0ScrPtr_02006e14(void);
extern void func_01ff8740(u32 value, void *dest, u32 size);
extern BOOL IsEntryFlagSet_020c0180(int flagSet, int entryIndex);
extern void *func_0202c478(u32 fileId, u32 heapId);
extern void func_0202b554(GraphicsView *view, void *file, int screenIndex, int characterIndex, int paletteIndex);
extern void DispatchByPartType_0202b4c0(int bgIndex, void *screen, void *character, void *palette, int mask, int flags);

void LoadEntryBackground_020bf0a4(MenuScene *scene)
{
    u32 *fileIndices = data_ov103_020c04b4;
    int entry = scene->entryIndex;
    u32 planes;

    if (scene->background.fileData != NULL) {
        NNSi_FndFreeFromDefaultHeap_0202a1c4(scene->background.fileData);
    }
    func_01ff8740(0, G2S_GetBG0ScrPtr_02006e14(), 0x800);
    planes = (REG_DB_DISPCNT & 0x1f00) >> 8;
    if (IsEntryFlagSet_020c0180(0, entry)) {
        planes |= 1;
    } else {
        planes &= ~1;
    }
    REG_DB_DISPCNT = (REG_DB_DISPCNT & ~0x1f00) | (planes << 8);
    scene->background.fileData = func_0202c478(((scene->archiveBase + 0x8000) & 0xfffffc) << 7 | 0x80000000 | (fileIndices[entry] & 0x1ff), 0xe);
    func_0202b554(&scene->background.view, scene->background.fileData, 0, 0, 0);
    DispatchByPartType_0202b4c0(4, scene->background.view.screen, scene->background.view.character, scene->background.view.palette, 0x1d, 2);
}
