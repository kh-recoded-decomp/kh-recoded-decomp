#include "nitro/types.h"

typedef struct MessageWindowTileView {
    int layer;
    u8 reserved04[8];
    BOOL fillPattern;
} MessageWindowTileView;

typedef struct MessageTileRow {
    u16 prefix[17];
    u16 pattern[15];
} MessageTileRow;

extern int func_ov001_0207123c(void);
extern MessageTileRow *func_ov027_020b9df0(int widgets, int layer);
extern void MarkTileTableRowDirty_020b9e00(int widgets, int layer);

void FillMessageWindowTilePattern_020794c8(MessageWindowTileView *window)
{
    int widgets = func_ov001_0207123c();
    MessageTileRow *rows = func_ov027_020b9df0(widgets, 9);

    if (window->fillPattern != 0) {
        int bottomRow = window->layer == 0 ? 8 : 23;
        int row;

        for (row = 0; row < 15; row++) {
            int column;
            if (row > bottomRow) {
                break;
            }
            for (column = 0; column < 15; column++) {
                rows[bottomRow - row].pattern[column] = (14 - row) * 15 + 0x70 + column;
            }
        }
        MarkTileTableRowDirty_020b9e00(widgets, 9);
    }
}
