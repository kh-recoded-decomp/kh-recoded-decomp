#include "nitro/types.h"

typedef struct {
    u8 pad_000[0x134];
    int pageIndex;
} Ov086Menu;

extern Ov086Menu *data_ov086_020c3000;
extern void func_ov086_020c080c(Ov086Menu *menu);

void SelectRecordPage_020c2060(int pageIndex)
{
    Ov086Menu *menu = data_ov086_020c3000;
    menu->pageIndex = pageIndex;
    func_ov086_020c080c(menu);
}
