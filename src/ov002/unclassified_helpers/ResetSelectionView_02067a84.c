#include "nitro/types.h"

typedef struct SelectionView {
    u8 pad_00[0x18];
    void *selection;
    s32 recordIds[22];
    u8 objSlots[22][16];
    u8 recordSlots[22][16];
    u8 extraSlots[22][16];
    u8 counts[22];
} SelectionView;

extern s32 data_ov002_0206af0c[];
extern void func_01ff8830(void *dst, int value, u32 size);
extern void ResolveCategorySelectionIds_02068548(SelectionView *view);

void ResetSelectionView_02067a84(SelectionView *view)
{
    int i = 0;

    func_01ff8830(view->recordIds, 0, sizeof(view->recordIds));
    func_01ff8830(view->objSlots, 0, sizeof(view->objSlots));
    func_01ff8830(view->recordSlots, 0, sizeof(view->recordSlots));
    func_01ff8830(view->extraSlots, 0, sizeof(view->extraSlots));
    func_01ff8830(view->counts, 0, sizeof(view->counts));
    if (view->selection == NULL) {
        for (; i < 20; i++) {
            view->recordIds[i] = data_ov002_0206af0c[i];
        }
    } else {
        ResolveCategorySelectionIds_02068548(view);
    }
}
