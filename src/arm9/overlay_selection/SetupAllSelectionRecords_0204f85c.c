#include "nitro/types.h"

typedef struct OverlaySelectionRecord OverlaySelectionRecord;
typedef struct GameState GameState;

extern GameState *data_0205fe0c;

extern void func_020506dc(int reload, int discardCached);
extern OverlaySelectionRecord *GetOverlaySelectionRecord_0204f768(u32 selectionIndex);
extern void func_02050b30(GameState *state, OverlaySelectionRecord *record, int param3, int param4);
extern void func_02050a44(void);
extern void func_0204fbcc(u32 selectionIndex, int kind);
extern void PackSelectionRecordEntry_0204fda4(u32 selectionIndex, int nameId, int entryIndex);

void SetupAllSelectionRecords_0204f85c(void)
{
    func_020506dc(0, 0);
    func_02050b30(data_0205fe0c, GetOverlaySelectionRecord_0204f768(0), 1, 1);
    func_02050a44();
    func_0204fbcc(1, 2);
    PackSelectionRecordEntry_0204fda4(1, 2, 0);
    func_0204fbcc(2, 1);
    PackSelectionRecordEntry_0204fda4(2, 1, 0);
}
