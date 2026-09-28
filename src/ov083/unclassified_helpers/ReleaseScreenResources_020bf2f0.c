#include "nitro/types.h"

typedef struct TextLayer {
    u8 pad_00[0x34];
} TextLayer;

typedef struct StringTable {
    void *buffer;
    u32 count;
    u8 *entries;
} StringTable;

typedef struct ScreenState {
    u8 pad_000[0xb8];
    TextLayer textLayers[2];
    u8 pad_120[0x150 - 0x120];
    StringTable strings;
    u8 pad_15c[0x168 - 0x15c];
    void *fileData;
} ScreenState;

typedef struct ResourceContainer ResourceContainer;

extern ResourceContainer *func_ov039_020bc1cc(void);
extern void *func_ov039_020bc1a4(void);
extern void FreePointerIfSet_020ba294(void **ptr);
extern void SweepElements_020b831c(void *elements);
extern void DestroyAllContainerElements_020b900c(ResourceContainer *container);
extern void func_ov027_020b903c(ResourceContainer *container);
extern BOOL DestroyFndObjectList_020014f0(TextLayer *layer);
extern void NNSi_FndFreeFromDefaultHeap_0202a1c4(void *block);

void ReleaseScreenResources_020bf2f0(ScreenState *screen) {
    ResourceContainer *container = func_ov039_020bc1cc();

    FreePointerIfSet_020ba294(&screen->strings.buffer);
    SweepElements_020b831c(func_ov039_020bc1a4());
    DestroyAllContainerElements_020b900c(container);
    func_ov027_020b903c(container);
    DestroyFndObjectList_020014f0(&screen->textLayers[0]);
    DestroyFndObjectList_020014f0(&screen->textLayers[1]);
    if (screen->fileData != NULL) {
        NNSi_FndFreeFromDefaultHeap_0202a1c4(screen->fileData);
    }
}
