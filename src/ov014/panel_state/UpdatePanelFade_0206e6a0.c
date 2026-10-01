#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct PanelSprite {
    u8 pad_00[0x8];
    fx32 scale;
} PanelSprite;

typedef struct PanelState {
    u8 pad_0000[0x6514];
    u8 spriteList[0xc9bc - 0x6514];
    u8 entryTable[0xcaac - 0xc9bc];
    fx32 baseScale;
    u8 pad_cab0[0x8];
    u32 activeEntry;
    PanelSprite *sprite;
    u8 pad_cac0[0xcb50 - 0xcac0];
    u8 *slotEntries[(0xcf74 - 0xcb50) / 4];
    s16 row;
    u8 pad_cf76[2];
    s16 column;
    u8 pad_cf7a[2];
    s16 slot;
    u8 pad_cf7e[0xcf92 - 0xcf7e];
    s8 fadeCount;
    s8 fadeDirection;
    u8 pad_cf94;
    s8 blinkTimer;
} PanelState;

extern PanelState *g_panelState_0206f9a0;
extern u8 data_ov014_0206f81c[][7];
extern void func_ov002_020681b8(void *list, PanelSprite *sprite, fx32 scale, fx32 one);
extern void func_ov002_020680a4(void *list, PanelSprite *sprite);
extern void func_ov002_02069190(void *table, u32 category, u32 entry);
extern void func_ov002_02069308(void *table, u32 category, u32 entry);
extern void SyncMismatchedCategoryEntries_020683bc(void *list, u32 entry, void *table, s32 flag);

void UpdatePanelFade_0206e6a0(void)
{
    if (g_panelState_0206f9a0->fadeDirection != 0) {
        PanelSprite *sprite;
        s32 level;
        fx32 scale;
        g_panelState_0206f9a0->fadeCount--;
        level = g_panelState_0206f9a0->fadeCount;
        if (g_panelState_0206f9a0->fadeDirection >= 0) {
            level = 4 - level;
        }
        scale = level << 10;
        sprite = g_panelState_0206f9a0->sprite;
        func_ov002_020681b8(g_panelState_0206f9a0->spriteList, sprite, scale, 0x1000);
        sprite->scale = (fx32)(((s64)g_panelState_0206f9a0->baseScale * scale + 0x800) >> 12);
        func_ov002_020680a4(g_panelState_0206f9a0->spriteList, sprite);
        if (g_panelState_0206f9a0->fadeCount <= 0) {
            g_panelState_0206f9a0->fadeDirection = 0;
        }
    }
    g_panelState_0206f9a0->blinkTimer++;
    if (g_panelState_0206f9a0->blinkTimer == 0) {
        u32 category = data_ov014_0206f81c[g_panelState_0206f9a0->row][g_panelState_0206f9a0->column];
        u32 entry = g_panelState_0206f9a0->slotEntries[category][g_panelState_0206f9a0->slot];
        func_ov002_02069190(g_panelState_0206f9a0->entryTable, category, entry);
        func_ov002_02069308(g_panelState_0206f9a0->entryTable, category, entry);
        return;
    }
    if (g_panelState_0206f9a0->blinkTimer > 16) {
        g_panelState_0206f9a0->blinkTimer = 16;
    }
    {
        s32 timer = g_panelState_0206f9a0->blinkTimer;
        if (timer >= 0 && timer < 16) {
            SyncMismatchedCategoryEntries_020683bc(g_panelState_0206f9a0->spriteList, g_panelState_0206f9a0->activeEntry, g_panelState_0206f9a0->entryTable, timer & 4);
        }
    }
}
