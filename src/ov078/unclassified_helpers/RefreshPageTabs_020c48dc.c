#include "nitro/types.h"

typedef struct PageMenu {
    u8 pad[0x24];
    void *nodes[8];
    u8 pad44[0x5d0 - 0x44];
    int cursor;
    int page;
} PageMenu;

extern void *func_ov039_020bc1bc(void);
extern void func_ov027_020b91c8(void *scene, void *node, int *offset, int flags);
extern BOOL IsGlobalPackedBitSet_02027304(int bit);
extern int ReadGlobalPackedBits_02027348(int bit, int width);
extern void SetEntrySlotsVisible_020b9580(void *scene, void *node, BOOL visible);
extern void func_ov027_020b96a0(void *scene, void *node, int mode);

void RefreshPageTabs_020c48dc(PageMenu *menu)
{
    void *scene = func_ov039_020bc1bc();
    int offset[2];
    int cursor;
    int extra;
    int count;
    int i;

    offset[0] = 0;
    offset[1] = menu->page << 16;
    func_ov027_020b91c8(scene, menu->nodes[1], offset, 3);
    cursor = menu->cursor;
    extra = IsGlobalPackedBitSet_02027304(cursor + 0xa01);
    count = ReadGlobalPackedBits_02027348(cursor * 2 + 0x9f7, 2);
    count = (u32)(extra != 0) + count;
    for (i = 0; i < count; i++) {
        BOOL inactive = TRUE;
        if (i == menu->page) {
            inactive = FALSE;
        }
        u8 *slot = (u8 *)menu + (i + 2) * 4;
        SetEntrySlotsVisible_020b9580(scene, *(void **)(slot + 0x24), inactive);
        SetEntrySlotsVisible_020b9580(scene, *(void **)(slot + 0x30), !inactive);
        func_ov027_020b96a0(scene, *(void **)(slot + 0x30), 0);
    }
}
