#include "nitro/types.h"

typedef struct PageMenu {
    u8 pad[0x24];
    void *nodes[11];
    u8 pad50[0x5d0 - 0x50];
    int cursor;
    int page;
} PageMenu;

extern void *func_ov039_020bc1bc(void);
extern BOOL IsGlobalPackedBitSet_02027304(int bit);
extern int ReadGlobalPackedBits_02027348(int bit, int width);
extern void SetEntrySlotsVisible_020b9580(void *scene, void *node, BOOL visible);

void ShowUnlockedPageTabs_020c4774(PageMenu *menu)
{
    void *scene = func_ov039_020bc1bc();
    int cursor = menu->cursor;
    int extra = IsGlobalPackedBitSet_02027304(cursor + 0xa01);
    int count = ReadGlobalPackedBits_02027348(cursor * 2 + 0x9f7, 2);

    switch ((u32)(extra != 0) + count) {
    case 0:
    case 1:
        SetEntrySlotsVisible_020b9580(scene, menu->nodes[2], FALSE);
        SetEntrySlotsVisible_020b9580(scene, menu->nodes[3], FALSE);
        SetEntrySlotsVisible_020b9580(scene, menu->nodes[4], FALSE);
        SetEntrySlotsVisible_020b9580(scene, menu->nodes[5], TRUE);
        SetEntrySlotsVisible_020b9580(scene, menu->nodes[6], FALSE);
        SetEntrySlotsVisible_020b9580(scene, menu->nodes[7], FALSE);
        break;
    case 2:
        SetEntrySlotsVisible_020b9580(scene, menu->nodes[2], FALSE);
        SetEntrySlotsVisible_020b9580(scene, menu->nodes[3], TRUE);
        SetEntrySlotsVisible_020b9580(scene, menu->nodes[4], FALSE);
        SetEntrySlotsVisible_020b9580(scene, menu->nodes[5], TRUE);
        SetEntrySlotsVisible_020b9580(scene, menu->nodes[6], FALSE);
        SetEntrySlotsVisible_020b9580(scene, menu->nodes[7], FALSE);
        break;
    case 3:
        SetEntrySlotsVisible_020b9580(scene, menu->nodes[2], FALSE);
        SetEntrySlotsVisible_020b9580(scene, menu->nodes[3], TRUE);
        SetEntrySlotsVisible_020b9580(scene, menu->nodes[4], TRUE);
        SetEntrySlotsVisible_020b9580(scene, menu->nodes[5], TRUE);
        SetEntrySlotsVisible_020b9580(scene, menu->nodes[6], FALSE);
        SetEntrySlotsVisible_020b9580(scene, menu->nodes[7], FALSE);
        break;
    }

    switch (ReadGlobalPackedBits_02027348(menu->cursor * 2 + 0x9f7, 2)) {
    case 0:
        SetEntrySlotsVisible_020b9580(scene, menu->nodes[8], FALSE);
        SetEntrySlotsVisible_020b9580(scene, menu->nodes[9], FALSE);
        SetEntrySlotsVisible_020b9580(scene, menu->nodes[10], FALSE);
        break;
    case 1:
        SetEntrySlotsVisible_020b9580(scene, menu->nodes[8], TRUE);
        SetEntrySlotsVisible_020b9580(scene, menu->nodes[9], FALSE);
        SetEntrySlotsVisible_020b9580(scene, menu->nodes[10], FALSE);
        break;
    case 2:
        SetEntrySlotsVisible_020b9580(scene, menu->nodes[8], TRUE);
        SetEntrySlotsVisible_020b9580(scene, menu->nodes[9], TRUE);
        SetEntrySlotsVisible_020b9580(scene, menu->nodes[10], FALSE);
        break;
    case 3:
        SetEntrySlotsVisible_020b9580(scene, menu->nodes[8], TRUE);
        SetEntrySlotsVisible_020b9580(scene, menu->nodes[9], TRUE);
        SetEntrySlotsVisible_020b9580(scene, menu->nodes[10], TRUE);
        break;
    }
}
