#include "nitro/types.h"

typedef struct {
    u8 pad[0x34];
    int scroll;
} GridTable;

typedef struct {
    u8 pad0[0x110a4];
    GridTable table;
    u8 pad1[0x11100 - 0x110a4 - sizeof(GridTable)];
    int direction;
} GridWork;

extern BOOL func_ov095_020c0a64(GridWork *work);
extern void func_ov095_020c0478(GridWork *work);
extern void func_ov095_020bfa18(int mode, GridWork *work);
extern BOOL PlaySoundEffect_0204d924(int seqArcNo, int index);
extern void SetPanelMode_020c11f0(int mode, GridWork *work);

void ConfirmGridMoveA_020bee6c(GridWork *work) {
    GridTable *table;

    if (!func_ov095_020c0a64(work)) {
        return;
    }
    table = &work->table;
    if (table->scroll < 0x100) {
        work->direction = 0;
    }
    if (table->scroll > 0x100) {
        work->direction = 1;
    }
    func_ov095_020c0478(work);
    func_ov095_020bfa18(-1, work);
    PlaySoundEffect_0204d924(0, 0);
    SetPanelMode_020c11f0(2, work);
}