#pragma optimization_level 1
#include "nitro/types.h"

typedef struct RecordPage {
    u32 recordId;
    u8 reserved04[0x108 - 4];
} RecordPage;

typedef struct RecordPageSelection {
    u32 parameter00;
    int cursor;
    int pageCount;
    BOOL useAdjacentPage;
    int direction;
    u8 reserved14[0x118 - 0x14];
    RecordPage pages[1];
} RecordPageSelection;

extern RecordPageSelection *GetActiveMenuScene(void);
extern BOOL IsRecordPageUnavailable(u32 recordId);

BOOL IsCurrentRecordPageUnavailable(void)
{
    RecordPageSelection *selection = GetActiveMenuScene();
    int pageIndex;

    if (selection->useAdjacentPage != 0) {
        int cursor;
        int pageCount;
        int numerator;
        if (selection->direction > 0) {
            cursor = selection->cursor;
            pageCount = selection->pageCount;
            numerator = pageCount + cursor - 1;
        } else {
            cursor = selection->cursor;
            pageCount = selection->pageCount;
            numerator = cursor + 1;
        }
        pageIndex = numerator % pageCount;
    } else {
        pageIndex = selection->cursor;
    }
    return IsRecordPageUnavailable(selection->pages[pageIndex].recordId);
}
