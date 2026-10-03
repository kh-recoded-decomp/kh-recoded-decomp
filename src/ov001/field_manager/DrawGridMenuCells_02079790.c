#include "nitro/types.h"

typedef struct {
    u8 data[0x34];
} TextWindow;

typedef struct GridLayout {
    s32 lastIndex;
    u8 pad_04[0xc];
    TextWindow *windows;
    u16 cellWidth;
    u16 cellHeight;
    u16 rows;
    u16 totalRows;
    u16 columns;
    u16 x;
    u16 y;
    u16 width;
    u16 height;
    u16 cursor;
    u16 scroll;
} GridLayout;

typedef struct GridMenu {
    u8 pad_00[0x54];
    GridLayout grid;
} GridMenu;

typedef struct TagRecord {
    u8 pad_00[4];
    u16 index;
    u8 pad_06[0x24 - 6];
    u8 visible : 1;
    u8 unk_24_1 : 7;
    u8 pad_25[0x2c - 0x25];
    void **callbacks;
} TagRecord;

extern void *GetSceneTagTracker_020711b0(void);
extern int func_ov001_0207123c(void);
extern u16 *UpdateWidgetLayerDefault_020b9df0(int layers, int layerIndex);
extern void func_ov027_020b9d54(int screen, int layer, int x, int y, int width, int height);
extern void func_ov027_020b9e00(int widgets, int layer);
extern void FillTextWindowBackground_02079770(GridLayout *grid, u16 *dst, u16 *other, int windowIndex, int x, int y, int scale);
extern void func_ov001_020795f0(u16 *target, int x, int y, int width, int height, int scale);
extern TagRecord *func_ov027_020b8390(void *tracker, int id);
extern void func_ov027_020b83e8(void *tracker, TagRecord *record, int value);
extern void TagTracker_InvokeCallback_020b8210(void *tracker, void *callback);
extern void PositionListRecords_020b8498(void *tracker, TagRecord *record, s16 y);
extern void apply_all_pending_entry_edits_020b84f4(void *tracker, TagRecord *record, s16 x, s16 y);

void DrawGridMenuCells_02079790(GridMenu *menu, BOOL hideCursor)
{
    GridLayout *grid;
    int row;
    int cursorX;
    int cursorY;
    int minX;
    int minY;
    int maxX;
    int maxY;
    int top;
    void *tracker;
    int screen;
    u16 *layerA;
    u16 *layerB;
    int columns;

    minX = -1;
    minY = -1;
    maxX = -1;
    maxY = -1;
    grid = &menu->grid;
    tracker = GetSceneTagTracker_020711b0();
    screen = func_ov001_0207123c();
    layerA = UpdateWidgetLayerDefault_020b9df0(screen, 10);
    layerB = UpdateWidgetLayerDefault_020b9df0(screen, 11);
    func_ov027_020b9d54(screen, 10, grid->x, grid->y, grid->width, grid->height - 2);
    func_ov027_020b9d54(screen, 11, grid->x, grid->y, grid->width, grid->height - 2);
    if (grid->cursor < grid->scroll) {
        grid->scroll = grid->cursor / grid->columns * grid->columns;
    }
    if (grid->cursor >= grid->scroll + grid->rows * grid->columns) {
        grid->scroll = (grid->cursor - (grid->rows - 1) * grid->columns) / grid->columns * grid->columns;
    }
    top = grid->y + grid->height / 2;
    top -= grid->rows * 2 / 2;
    for (row = 0; row < grid->rows; row++) {
        int y = top + row * 2;
        int column;

        for (column = 0; column < (columns = grid->columns); column++) {
            int x;
            int index;
            u16 cellWidth = grid->cellWidth;

            x = grid->x + grid->width * (column + 1) / (columns + 1) - cellWidth / 2;
            index = grid->scroll + (column + columns * row);
            if (index > grid->lastIndex) {
                func_ov027_020b9e00(screen, 10);
                func_ov027_020b9e00(screen, 11);
                return;
            }
            if (grid->cursor == index) {
                cursorX = x;
                cursorY = y;
            }
            if (minX == -1) {
                maxX = x + cellWidth;
                minX = x;
                minY = y;
                maxY = y + grid->cellHeight;
            } else {
                if (x < minX) {
                    minX = x;
                }
                if (x + cellWidth > maxX) {
                    maxX = x + cellWidth;
                }
                if (y < minY) {
                    minY = y;
                }
                if (y + grid->cellHeight > maxY) {
                    maxY = y + grid->cellHeight;
                }
            }
            FillTextWindowBackground_02079770(grid, layerA, layerB, index, x, y, 0xe000);
        }
    }
    func_ov001_020795f0(layerB, minX - 3, minY - 1, maxX - minX + 4, maxY - minY + 1, 0xe000);
    if (grid->totalRows > grid->rows) {
        TagRecord *up = func_ov027_020b8390(tracker, 0xd);
        TagRecord *down = func_ov027_020b8390(tracker, 0xe);

        if (up->visible == 1) {
            if (grid->scroll == 0) {
                func_ov027_020b83e8(tracker, up, 0);
            } else {
                TagTracker_InvokeCallback_020b8210(tracker, up->callbacks[up->index]);
            }
        } else if (grid->scroll != 0) {
            PositionListRecords_020b8498(tracker, up, minY - 3);
            func_ov027_020b83e8(tracker, up, 1);
        }
        if (down->visible == 1) {
            if (grid->totalRows == grid->scroll + grid->rows) {
                func_ov027_020b83e8(tracker, down, 0);
            } else {
                TagTracker_InvokeCallback_020b8210(tracker, down->callbacks[down->index]);
            }
        } else if (grid->scroll + grid->rows < grid->totalRows) {
            PositionListRecords_020b8498(tracker, down, maxY + 2);
            func_ov027_020b83e8(tracker, down, 1);
        }
    }
    if (!hideCursor) {
        TagRecord *cursor = func_ov027_020b8390(tracker, 6);
        apply_all_pending_entry_edits_020b84f4(tracker, cursor, cursorX - 2, cursorY + 1);
        func_ov027_020b83e8(tracker, cursor, 1);
    }
    func_ov027_020b9e00(screen, 10);
    func_ov027_020b9e00(screen, 11);
}





