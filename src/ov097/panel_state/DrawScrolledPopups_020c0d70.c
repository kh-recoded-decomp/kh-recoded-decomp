#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u8 pad_00[0x14];
    fx32 y;
    u8 pad_18[0x14];
} PopupEntry;

typedef struct {
    int entryIndex;
    u8 pad_0004[0xeea8 - 4];
    PopupEntry popups[10];
    int popupCount;
    u8 pad_f064[4];
    int scrollRow;
} MenuScene;

extern void ResetMenuOrthoCamera_020c19ac(void);
extern BOOL IsEntryFlagSet_020c1474(int flagSet, int entryIndex);
extern void func_01ff89a8(const void *src, void *dst, u32 size);
extern void NNS_FndInitListWithOffset0_020c1d98(void *list);
extern void _fp_init_020c1a44(void);

#define ROW_TO_FX32(row) ((fx32)((float)(row) > 0 ? 0.5f + 4096.0f * (float)(row) : 4096.0f * (float)(row) - 0.5f))

void DrawScrolledPopups_020c0d70(MenuScene *scene)
{
    int entryIndex = scene->entryIndex;
    PopupEntry popup;
    int i;

    ResetMenuOrthoCamera_020c19ac();
    if (IsEntryFlagSet_020c1474(0, entryIndex)) {
        for (i = 0; i < scene->popupCount; i++) {
            func_01ff89a8(&scene->popups[i], &popup, sizeof(PopupEntry));
            popup.y += ROW_TO_FX32(scene->scrollRow);
            NNS_FndInitListWithOffset0_020c1d98(&popup);
        }
    }
    _fp_init_020c1a44();
}
