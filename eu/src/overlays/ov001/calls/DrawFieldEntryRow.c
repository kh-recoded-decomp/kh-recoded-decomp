#include "nitro/types.h"

typedef struct FieldEntry {
    u8 pad_00[0x10];
    s32 kind;
    u8 pad_14[0x8];
    void *labels[2];
    s32 labelIndex;
    u16 flags;
    u16 count;
} FieldEntry;

extern void *GetSceneTagTracker(void);
extern void SelectListNodeOrFirst(void *text, void *node);
extern void SetFieldAt2C(void *text, u16 value);
extern void WriteTileBlockToScreen(void *text, u16 *screen, int x, int y, int palette);
extern void *FindActiveRecordById(void *pool, u16 recordId);
extern void func_ov027_020b82a4(void *pool, void *record, u8 palette);
extern void func_ov027_020b824c(void *tracker, void *record, s16 x, s16 y);
extern void Text_UploadTileBuffer(void *text);

void DrawFieldEntryRow(void *text, FieldEntry *entry, u16 *screen, int slot, int x, int y, int color)
{
    void *tracker = GetSceneTagTracker();
    u16 palette = color;
    int digit;
    s16 count;
    int tens;
    int ones;

    SelectListNodeOrFirst(text, entry->labels[entry->labelIndex]);
    SetFieldAt2C(text, (slot + 1) * 0x10 + 0x330);
    if (!(entry->flags & 1) || !(entry->flags & 4)) {
        palette = 10;
    }
    WriteTileBlockToScreen(text, screen, x, y, palette);
    switch (entry->kind) {
    case 3:
        count = entry->count > 9 ? 9 : entry->count;
        digit = count + 0x28;
        func_ov027_020b82a4(tracker, FindActiveRecordById(tracker, digit), palette);
        func_ov027_020b824c(tracker, FindActiveRecordById(tracker, digit), x + 7, y + 1);
        break;
    case 5:
        count = entry->count > 99 ? 99 : entry->count;
        if (count >= 10) {
            tens = count / 10 + 0x28;
            func_ov027_020b82a4(tracker, FindActiveRecordById(tracker, tens), palette);
            func_ov027_020b824c(tracker, FindActiveRecordById(tracker, tens), x + 7, y + 1);
            ones = count % 10;
            func_ov027_020b82a4(tracker, FindActiveRecordById(tracker, ones + 0x28), palette);
            func_ov027_020b824c(tracker, FindActiveRecordById(tracker, ones + 0x46), x + 8, y + 1);
        } else {
            digit = count + 0x28;
            func_ov027_020b82a4(tracker, FindActiveRecordById(tracker, digit), palette);
            func_ov027_020b824c(tracker, FindActiveRecordById(tracker, digit), x + 7, y + 1);
        }
        break;
    }
    Text_UploadTileBuffer(text);
    entry->flags &= ~2;
}
