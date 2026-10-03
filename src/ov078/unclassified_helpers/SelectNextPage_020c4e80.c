#include "nitro/types.h"

typedef struct PageMenu {
    u8 pad[0x5d0];
    int cursor;
    int page;
} PageMenu;

extern u16 data_02060500;
extern BOOL IsGlobalPackedBitSet_02027304(int bit);
extern int ReadGlobalPackedBits_02027348(int bit, int width);
extern void PlaySoundEffect_0204d924(int bank, int id);
extern void func_ov078_020c48dc(PageMenu *menu);
extern void func_ov078_020c4b18(PageMenu *menu);

void SelectNextPage_020c4e80(PageMenu *menu)
{
    int oldPage = menu->page;
    int cursor = menu->cursor;
    int extra = IsGlobalPackedBitSet_02027304(cursor + 0xa01);
    int count = ReadGlobalPackedBits_02027348(cursor * 2 + 0x9f7, 2);

    if ((u32)(extra != 0) + count != 0) {
        cursor = menu->cursor;
        extra = IsGlobalPackedBitSet_02027304(cursor + 0xa01);
        count = ReadGlobalPackedBits_02027348(cursor * 2 + 0x9f7, 2);
        if (menu->page == (u32)(extra != 0) + count - 1) {
            if (data_02060500 & 0x80) {
                menu->page = 0;
            }
        } else {
            menu->page = menu->page + 1;
        }
        if (oldPage != menu->page) {
            PlaySoundEffect_0204d924(0, 0);
            func_ov078_020c48dc(menu);
            func_ov078_020c4b18(menu);
        }
    }
}
