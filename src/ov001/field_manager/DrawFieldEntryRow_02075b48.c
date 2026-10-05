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

extern void *GetSceneTagTracker_020711b0(void);
extern void SelectListNodeOrFirst_020019b8(void *text, void *node);
extern void SetFieldAt0x2c_02001b1c(void *text, u16 value);
extern void func_ov001_02075584(void *text, u16 *screen, int x, int y, int palette);
extern void *FindActiveRecordById_020b8184(void *pool, u16 recordId);
extern void func_ov027_020b8284(void *pool, void *record, u8 palette);
extern void func_ov027_020b822c(void *tracker, void *record, s16 x, s16 y);
extern void Text_UploadTileBuffer_02001520(void *text);

void DrawFieldEntryRow_02075b48(void *text, FieldEntry *entry, u16 *screen, int slot, int x, int y, int color)
{
    void *tracker = GetSceneTagTracker_020711b0();
    u16 palette = color;
    int digit;
    s16 count;
    int tens;
    int ones;

    SelectListNodeOrFirst_020019b8(text, entry->labels[entry->labelIndex]);
    SetFieldAt0x2c_02001b1c(text, (slot + 1) * 0x10 + 0x330);
    if (!(entry->flags & 1) || !(entry->flags & 4)) {
        palette = 10;
    }
    func_ov001_02075584(text, screen, x, y, palette);
    switch (entry->kind) {
    case 3:
        count = entry->count > 9 ? 9 : entry->count;
        digit = count + 0x28;
        func_ov027_020b8284(tracker, FindActiveRecordById_020b8184(tracker, digit), palette);
        func_ov027_020b822c(tracker, FindActiveRecordById_020b8184(tracker, digit), x + 7, y + 1);
        break;
    case 5:
        count = entry->count > 99 ? 99 : entry->count;
        if (count >= 10) {
            tens = count / 10 + 0x28;
            func_ov027_020b8284(tracker, FindActiveRecordById_020b8184(tracker, tens), palette);
            func_ov027_020b822c(tracker, FindActiveRecordById_020b8184(tracker, tens), x + 7, y + 1);
            ones = count % 10;
            func_ov027_020b8284(tracker, FindActiveRecordById_020b8184(tracker, ones + 0x28), palette);
            func_ov027_020b822c(tracker, FindActiveRecordById_020b8184(tracker, ones + 0x46), x + 8, y + 1);
        } else {
            digit = count + 0x28;
            func_ov027_020b8284(tracker, FindActiveRecordById_020b8184(tracker, digit), palette);
            func_ov027_020b822c(tracker, FindActiveRecordById_020b8184(tracker, digit), x + 7, y + 1);
        }
        break;
    }
    Text_UploadTileBuffer_02001520(text);
    entry->flags &= ~2;
}
