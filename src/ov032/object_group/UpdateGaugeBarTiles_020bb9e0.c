#include "nitro/types.h"

typedef struct {
    const void *source;
    u8 *tiles;
    u8 pad_08[0x18];
    int level;
    int targetLevel;
    BOOL snap;
} GaugeBar;

extern void MIi_CpuCopyFast_01ff878c(const void *src, void *dst, u32 size);
extern void DrawTileColumnPattern_020bb98c(u8 *tiles, u16 x, int pattern);
extern int GFXi_EnqueueCommand_02014090(int command, int offset, void *data, int size);

void UpdateGaugeBarTiles_020bb9e0(GaugeBar *bar)
{
    int x;

    if (bar->snap) {
        bar->level = bar->targetLevel;
        bar->snap = FALSE;
    } else {
        int level = bar->level;
        int target = bar->targetLevel;
        if (target < level) {
            level -= 2;
            bar->level = level;
            if (target < level) {
                target = level;
            }
            bar->level = target;
        } else if (target > level) {
            level += 2;
            bar->level = level;
            if (target > level) {
                target = level;
            }
            bar->level = target;
        }
    }
    MIi_CpuCopyFast_01ff878c(bar->source, bar->tiles, 0x160);
    for (x = 0; x < bar->level; x++) {
        DrawTileColumnPattern_020bb98c(bar->tiles, x, 0);
    }
    for (; x < 0x57; x++) {
        DrawTileColumnPattern_020bb98c(bar->tiles, x, 1);
    }
    GFXi_EnqueueCommand_02014090(7, 0x50a0, bar->tiles, 0x160);
}
